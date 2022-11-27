#include "gameplayState.h"

#include <iostream>
#include "system/draw.h"
#include "gameLogic/gameLogic.h"
#include "gameScreens/gameStatesEnum.h"

static bool firstTime = true;
extern float backgroundScale;

GameplayState::GameplayState()
{
    character = new Character;
    obstacles.push_back(new Obstacle());
    initTextures();
    initAudios();
}

GameplayState::~GameplayState()
{
    delete character;
    for (Bullet* bullet : bullets)
    {
        delete bullet;
    }
    for (Obstacle* obstacle : obstacles)
    {
        delete obstacle;
    }
    std::cout << "Gameplay state has been destroyed.";
}

void GameplayState::gameLogic()
{
    if (IsKeyDown(KEY_ESCAPE))backToMenu();

    if (character->isAlive())
    {
        update();
    }
    else
    {
        backToMenu();
    }
}

void GameplayState::backToMenu()
{
    setGameState(GameStates::Menu);
    character->reset();
    for (Obstacle* obstacle : obstacles)
    {
        obstacle->modifyHP(-50);
    }
    firstTime = true;
    unloadTextures();
    character = new Character;
    
    obstacles.push_back(new Obstacle());
    initTextures();
    initAudios();
}

void GameplayState::update()
{
    for (Obstacle* obstacle : obstacles)
    {
        if (obstacle->isAlive())
        {
            obstacle->changePosX();
            if (isCharacterObstacleColliding(character, obstacle)) character->setHP(-1);
        }
    }
    character->update();
    bulletBehaviour();
    wheelRotation += GetFrameTime() * character->getSpeed();
    BackgroundParalax();
}

void GameplayState::bulletBehaviour()
{
    if (IsKeyReleased(KEY_W)) bullets.push_back(character->shootUp(characterBullet, bulletSound));
    if (IsKeyReleased(KEY_F)) bullets.push_back(character->shootRight(characterBullet, bulletSound));

    for (Bullet* bullet : bullets)
    {
        bullet->changeBulletPosition();
    }

    for (Bullet* bullet : bullets)
    {
        for (Obstacle* obstacle : obstacles)
        {
            if (obstacle->isAlive() && bullet->isActive())
            {
                if (isObstacleBulletColliding(obstacle, bullet))
                {
                    bullet->setActive(false);
                    obstacle->modifyHP(-1);
                    if (!obstacle->isAlive())
                    {
                        character->addScore(20);
                    }
                }
            }
        }
    }
}

void GameplayState::initTextures()
{
    characterVehicle = LoadTexture("res/entities/player_car.png");
    characterWheel = LoadTexture("res/entities/wheel1.png");
    obstacleBike = LoadTexture("res/entities/enemy_bike.png");
    paralaxBackground = LoadTexture("res/montain_bakground.png");
    paralaxMidground = LoadTexture("res/mountain_midground.png");
    paralaxForeground = LoadTexture("res/mountain_foreground.png");
    characterBullet = LoadTexture("res/entities/player_bullet.png");
}

void GameplayState::initAudios()
{
    bulletSound = LoadSound("res/audios/bulletFired.wav");
}


void GameplayState::unloadTextures()
{
    UnloadTexture(characterVehicle);
    UnloadTexture(characterWheel);
    UnloadTexture(obstacleBike);
    UnloadTexture(paralaxBackground);
    UnloadTexture(paralaxMidground);
    UnloadTexture(paralaxForeground);
}


void GameplayState::drawGame()
{
    drawBackground();
    drawForeground();
    drawGUI();
}

void GameplayState::drawBackground() const
{
    static float rotation = 0;
    drawTexture(paralaxBackground, {scrollingBack, 0}, rotation, backgroundScale, WHITE);
    drawTexture(paralaxBackground, {paralaxBackground.width * backgroundScale + scrollingBack, 0}, rotation,
                backgroundScale,
                WHITE);

    drawTexture(paralaxMidground, {scrollingMid, 0}, rotation, backgroundScale, WHITE);
    drawTexture(paralaxMidground, {paralaxMidground.width * backgroundScale + scrollingMid, 0}, rotation,
                backgroundScale,
                WHITE);
}

void GameplayState::drawForeground() const
{
    static float rotation = 0;

    drawCharacter();
    drawObstacles();

    for (Bullet* bullet : bullets)
    {
        bullet->drawBullet();
    }

    drawTexture(paralaxForeground, {scrollingFore, 0}, rotation, backgroundScale, WHITE);
    drawTexture(paralaxForeground, {paralaxForeground.width * backgroundScale + scrollingFore, 0}, rotation,
                backgroundScale, WHITE);
}

void GameplayState::drawCharacter() const
{
    float vehicleScale = backgroundScale * 4;
    drawTexture(characterVehicle, {
                    character->getBody().x - characterVehicle.width / 4.3f,
                    character->getBody().y - characterVehicle.height / 1.2f
                }, 0, vehicleScale, RAYWHITE);

    float wheelX = character->getBody().x + vehicleScale;
    float wheelY = character->getBody().y + vehicleScale * 2;
    float wheelWidth = static_cast<float>(characterWheel.width);
    float wheelHeight = static_cast<float>(characterWheel.height);
    const Vector2 origin = {wheelWidth, wheelHeight};
    DrawTexturePro(characterWheel, {0, 0, wheelWidth, wheelHeight},
                   {wheelX + wheelWidth * 1.73f, wheelY + wheelHeight * 3, 50, 50}, origin, wheelRotation,RAYWHITE);

    //character->draw();
}

void GameplayState::drawObstacles() const
{
    for (Obstacle* obstacle : obstacles)
    {
        if (obstacle->isAlive())
        {
            float textureX = obstacle->getBody().x - obstacleBike.width;
            float textureY = obstacle->getBody().y - obstacleBike.height;

            drawTexture(obstacleBike, {textureX, textureY}, 0, 3 * backgroundScale, RAYWHITE);
            //DrawTextureRec(obstacleBike, {0, 0, -static_cast<float>(obstacleBike.width), static_cast<float>(obstacleBike.height)}, {textureX, textureY},                           RAYWHITE);
            //DrawTexturePro(obstacleBike, {0, 0, -static_cast<float>(obstacleBike.width), static_cast<float>(obstacleBike.height)}, {textureX, textureY},                           RAYWHITE);
        }
    }
}

void GameplayState::drawGUI()
{
    const int posX = GetScreenWidth() / 30;
    const int posY = GetScreenHeight() / 40;
    const int fontSize = GetScreenWidth() / 35;
    const int textMeasured = MeasureText("Score: %04i", fontSize * 2);
    DrawText(TextFormat("Score: %04i", character->getScore()), posX, posY, fontSize, RED);
    DrawText(TextFormat("Hp: %01i", character->getHP()), posX + textMeasured, posY, fontSize, RED);
}

void GameplayState::BackgroundParalax()
{
    const float paralaxSpeed = character->getSpeed() / 2;
    scrollingBack -= 0.1f * GetFrameTime() * paralaxSpeed;
    scrollingMid -= 0.5f * GetFrameTime() * paralaxSpeed;
    scrollingFore -= 1.0f * GetFrameTime() * paralaxSpeed;

    if (scrollingBack <= -paralaxBackground.width * backgroundScale) scrollingBack = 0;
    if (scrollingMid <= -paralaxMidground.width * backgroundScale) scrollingMid = 0;
    if (scrollingFore <= -paralaxForeground.width * backgroundScale) scrollingFore = 0;
}
