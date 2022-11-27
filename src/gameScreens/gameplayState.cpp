#include "gameplayState.h"

#include <iostream>
#include "system/draw.h"
#include "gameLogic/gameLogic.h"
#include "gameScreens/gameStatesEnum.h"

static bool firstTime = true;
extern float backgroundScale;
extern bool secondPlayerActive;

GameplayState::GameplayState()
{
    characterP1 = new Character(false);
    characterP2 = new Character(true);
    obstacles.push_back(new Obstacle(Obstacle::bike));
    obstacles.push_back(new Obstacle(Obstacle::helicopter));
    initTextures();
    initAudios();
}

GameplayState::~GameplayState()
{
    delete characterP1;
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
    if (firstTime)
    {
        if (secondPlayerActive)
        {
            characterP2Vehicle = LoadTexture("res/entities/playerTwo_car.png");
            characterP1Vehicle = LoadTexture("res/entities/playerOne_car.png");
            characterP2->modifyFloorLevel(.99f);
            characterP2->setX(characterP2->getBody().x+characterP2->getBody().width);
        }
        firstTime = false;
    }
    if (characterP1->isAlive() || characterP2->isAlive())
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
    characterP1->reset();
    for (Obstacle* obstacle : obstacles)
    {
        obstacle->modifyHP(-50);
    }
    firstTime = true;
    unloadTextures();
    characterP1 = new Character(false);
    characterP2 = new Character(true);

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
            obstacle->move();
            if (isCharacterObstacleColliding(characterP1, obstacle)) characterP1->setHP(-1);
            if (isCharacterObstacleColliding(characterP2, obstacle)) characterP2->setHP(-1);
        }
    }
    characterP1->update();
    if (secondPlayerActive) characterP2->update();
    bulletBehaviour();
    wheelRotation += GetFrameTime() * characterP1->getSpeed();
    BackgroundParalax();
}

void GameplayState::bulletBehaviour()
{
    if (!secondPlayerActive)
    {
        if (IsKeyReleased(KEY_W)) bullets.push_back(characterP1->shootUp(characterBullet, bulletSound));
        if (IsKeyReleased(KEY_F)) bullets.push_back(characterP1->shootRight(characterBullet, bulletSound));
    }
    else
    {
        if (IsKeyReleased(KEY_W)) bullets.push_back(characterP1->shootUp(characterBullet, bulletSound));
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) bullets.push_back(
            characterP2->shootRight(characterBullet, bulletSound));
    }

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
                        characterP1->addScore(20);
                    }
                }
            }
        }
    }
}

void GameplayState::initTextures()
{
    characterP1Vehicle = LoadTexture("res/entities/player_car.png");
    characterWheel = LoadTexture("res/entities/wheel1.png");
    obstacleBike = LoadTexture("res/entities/enemy_bike.png");
    paralaxBackground = LoadTexture("res/montain_bakground.png");
    paralaxMidground = LoadTexture("res/mountain_midground.png");
    paralaxForeground = LoadTexture("res/mountain_foreground.png");
    characterBullet = LoadTexture("res/entities/player_bullet.png");
    obstacleHelicopter = LoadTexture("res/entities/enemy_helicopter.png");
}

void GameplayState::initAudios()
{
    bulletSound = LoadSound("res/audios/bulletFired.wav");
}


void GameplayState::unloadTextures()
{
    UnloadTexture(characterP1Vehicle);
    UnloadTexture(characterWheel);
    UnloadTexture(obstacleBike);
    UnloadTexture(paralaxBackground);
    UnloadTexture(paralaxMidground);
    UnloadTexture(paralaxForeground);
    UnloadTexture(characterBullet);
    UnloadTexture(obstacleHelicopter);
    if (secondPlayerActive) characterP2Vehicle = LoadTexture("res/entities/playerTwo_car.png");
}

void GameplayState::unloadSounds()
{
    UnloadSound(bulletSound);
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
    drawTexture(paralaxBackground, {static_cast<float>(paralaxBackground.width) * backgroundScale + scrollingBack, 0},
                rotation,
                backgroundScale, WHITE);

    drawTexture(paralaxMidground, {scrollingMid, 0}, rotation, backgroundScale, WHITE);
    drawTexture(paralaxMidground, {static_cast<float>(paralaxMidground.width) * backgroundScale + scrollingMid, 0},
                rotation,
                backgroundScale, WHITE);
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
    drawTexture(paralaxForeground, {static_cast<float>(paralaxForeground.width) * backgroundScale + scrollingFore, 0},
                rotation,
                backgroundScale, WHITE);
}

void GameplayState::drawCharacter() const
{
    float vehicleScale = backgroundScale * 4;

    drawTexture(characterP1Vehicle, {
                    characterP1->getBody().x - static_cast<float>(characterP1Vehicle.width) / 4.3f,
                    characterP1->getBody().y - static_cast<float>(characterP1Vehicle.height) / 1.2f
                }, 0, vehicleScale, RAYWHITE);

    float wheelX = characterP1->getBody().x + vehicleScale;
    float wheelY = characterP1->getBody().y + vehicleScale * 2;
    float wheelWidth = static_cast<float>(characterWheel.width);
    float wheelHeight = static_cast<float>(characterWheel.height);

    const Vector2 origin = {wheelWidth, wheelHeight};

    DrawTexturePro(characterWheel, {0, 0, wheelWidth, wheelHeight},
                   {wheelX + wheelWidth * 1.73f, wheelY + wheelHeight * 3, 50, 50}, origin, wheelRotation,RAYWHITE);
    
    if (secondPlayerActive)
    {
        drawTexture(characterP2Vehicle, {
                    characterP2->getBody().x - static_cast<float>(characterP2Vehicle.width) / 4.3f,
                    characterP2->getBody().y - static_cast<float>(characterP2Vehicle.height) / 1.2f
                }, 0, vehicleScale, RAYWHITE);

        float wheelX2 = characterP2->getBody().x + vehicleScale;
        float wheelY2 = characterP2->getBody().y + vehicleScale * 2;
        float wheelWidth2 = static_cast<float>(characterWheel.width);
        float wheelHeight2 = static_cast<float>(characterWheel.height);

        const Vector2 origin2 = {wheelWidth2, wheelHeight2};

        DrawTexturePro(characterWheel, {0, 0, wheelWidth2, wheelHeight2},
                       {wheelX2 + wheelWidth2 * 1.73f, wheelY2 + wheelHeight2 * 3, 50, 50}, origin2, wheelRotation,RAYWHITE);
    }
}

void GameplayState::drawObstacles() const
{
    for (Obstacle* obstacle : obstacles)
    {
        float textureX = obstacle->getBody().x - static_cast<float>(obstacleBike.width);
        float textureY = obstacle->getBody().y - static_cast<float>(obstacleBike.height);

        if (obstacle->isAlive())
        {
            switch (obstacle->getType())
            {
            case Obstacle::helicopter:
                drawTexture(obstacleHelicopter, {textureX, textureY}, 0, 3 * backgroundScale, RAYWHITE);
                break;
            case Obstacle::bike:
            case Obstacle::truck:
            default:
                drawTexture(obstacleBike, {textureX, textureY}, 0, 3 * backgroundScale, RAYWHITE);
            }
        }
    }
}

void GameplayState::drawGUI() const
{
    const int posX = GetScreenWidth() / 30;
    const int posY = GetScreenHeight() / 40;
    const int fontSize = GetScreenWidth() / 35;
    const int textMeasured = MeasureText("Score: %04i", fontSize * 2);
    DrawText(TextFormat("Score: %04i", characterP1->getScore()), posX, posY, fontSize, RED);
    DrawText(TextFormat("Hp: %01i", characterP1->getHP()), posX + textMeasured, posY, fontSize, RED);
}

void GameplayState::BackgroundParalax()
{
    const float paralaxSpeed = characterP1->getSpeed() / 2;
    scrollingBack -= 0.1f * GetFrameTime() * paralaxSpeed;
    scrollingMid -= 0.5f * GetFrameTime() * paralaxSpeed;
    scrollingFore -= 1.0f * GetFrameTime() * paralaxSpeed;

    if (scrollingBack <= static_cast<float>(-paralaxBackground.width) * backgroundScale) scrollingBack = 0;
    if (scrollingMid <= static_cast<float>(-paralaxMidground.width) * backgroundScale) scrollingMid = 0;
    if (scrollingFore <= static_cast<float>(-paralaxForeground.width) * backgroundScale) scrollingFore = 0;
}
