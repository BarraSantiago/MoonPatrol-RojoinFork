#include "gameplayState.h"

#include <iostream>
#include "system/draw.h"
#include "gameLogic/gameLogic.h"
#include "gameScreens/gameStatesEnum.h"

static bool firstTime = true;
extern float backgroundScale;
extern bool secondPlayerActive;

void drawCompleteVehicle(Texture2D vehicle, Texture2D wheel, Vector2 pos, float rotation);


GameplayState::GameplayState()
{
    characterP1 = new Character(false);
    characterP2 = new Character(true);
    initTextures();
}

GameplayState::~GameplayState()
{
    delete characterP1;
    delete characterP2;
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
        checkPlayerTextures();
        airOriginalTimer = 7;
        groundOriginalTimer = 4;
    }

    if ((characterP1->isAlive() && !secondPlayerActive) || (characterP1->isAlive() && characterP2->isAlive()))
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

    for (Obstacle* obstacle : obstacles)
    {
        obstacle->modifyHP(-50);
    }

    firstTime = true;

    characterP1->reset();
    characterP2->reset();

    unloadTextures();
    initTextures();
}

void GameplayState::checkPlayerTextures()
{
    if (secondPlayerActive)
    {
        characterP1Vehicle = LoadTexture("res/entities/playerOne_car.png");
        characterP2->modifyFloorLevel(.99f);
        characterP2->setX(characterP2->getBody().x + characterP2->getBody().width);
    }
    else
    {
        characterP1Vehicle = LoadTexture("res/entities/player_car.png");
    }
    firstTime = false;
}

void GameplayState::update()
{
    for (Obstacle* obstacle : obstacles)
    {
        if (obstacle->isAlive())
        {
            obstacle->move();
            if (isCharacterObstacleColliding(characterP1, obstacle)) characterP1->setHP(-1);
            if (secondPlayerActive)
            {
                if (isCharacterObstacleColliding(characterP2, obstacle)) characterP2->setHP(-1);
            }
        }
    }
    spawnEnemies();
    characterP1->update();
    if (secondPlayerActive) characterP2->update();
    bulletBehaviour();
    wheelRotation += GetFrameTime() * characterP1->getSpeed();
    BackgroundParalax();
}

void GameplayState::bulletBehaviour()
{
    if (IsKeyReleased(KEY_W)) bullets.push_back(characterP1->shootUp(characterBullet));
    if (!secondPlayerActive)
    {
        if (IsKeyReleased(KEY_F)) bullets.push_back(characterP1->shootRight(characterBullet));
    }
    else
    {
        if (IsKeyReleased(KEY_RIGHT_CONTROL))
            bullets.push_back(characterP2->shootRight(characterBullet));
    }

    for (Bullet* bullet : bullets)
    {
        if (!bullet->isActive())
        {
            bullet->~Bullet();
            continue;
        }
        bullet->changeBulletPosition();

        for (Obstacle* obstacle : obstacles)
        {
            if (!obstacle->isAlive()) continue;
            if (!isObstacleBulletColliding(obstacle, bullet)) continue;

            bullet->setActive(false);
            obstacle->modifyHP(-1);

            if (!obstacle->isAlive())
            {
                characterP1->addScore(20);
            }
        }
    }
}

void GameplayState::initTextures()
{
    characterP1Vehicle = LoadTexture("res/entities/player_car.png");
    characterP2Vehicle = LoadTexture("res/entities/playerTwo_car.png");
    characterWheel = LoadTexture("res/entities/wheel1.png");
    characterBullet = LoadTexture("res/entities/player_bullet.png");
    obstacleBike = LoadTexture("res/entities/enemy_bike.png");
    obstacleHelicopter = LoadTexture("res/entities/enemy_helicopter.png");
    paralaxBackground = LoadTexture("res/montain_bakground.png");
    paralaxMidground = LoadTexture("res/mountain_midground.png");
    paralaxForeground = LoadTexture("res/mountain_foreground.png");
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
    UnloadTexture(characterP2Vehicle);
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
    drawCompleteVehicle(characterP1Vehicle, characterWheel, {characterP1->getBody().x, characterP1->getBody().y},
                        wheelRotation);
    if (secondPlayerActive)
    {
        drawCompleteVehicle(characterP2Vehicle, characterWheel, {characterP2->getBody().x, characterP2->getBody().y},
                            wheelRotation);
    }
}

void drawCompleteVehicle(Texture2D vehicle, Texture2D wheel, Vector2 pos, float rotation)
{
    float vehicleScale = backgroundScale * 4;

    drawTexture(vehicle, {
                    pos.x - static_cast<float>(vehicle.width) / 4.3f,
                    pos.y - static_cast<float>(vehicle.height) / 1.2f
                }, 0, vehicleScale, RAYWHITE);

    float wheelWidth = static_cast<float>(wheel.width);
    float wheelHeight = static_cast<float>(wheel.height);
    float wheelX = pos.x + vehicleScale + wheelWidth * 1.73f;
    float wheelX2 = pos.x + vehicleScale + wheelWidth * 1.73f + vehicle.width * 2;
    float wheelY = pos.y + vehicleScale * 1.7f;

    const Vector2 origin = {wheelWidth, wheelHeight};

    DrawTexturePro(wheel, {0, 0, wheelWidth, wheelHeight},
                   {wheelX, wheelY + wheelHeight * 3, 50, 50}, origin, rotation,RAYWHITE);

    DrawTexturePro(wheel, {0, 0, wheelWidth, wheelHeight},
                   {wheelX2, wheelY + wheelHeight * 3, 50, 50},
                   origin, rotation,RAYWHITE);
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
    if (secondPlayerActive)
    {
        DrawText(TextFormat("Hp p2: %01i", characterP2->getHP()), posX + textMeasured * 2, posY, fontSize, ORANGE);
    }
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

void GameplayState::spawnEnemies()
{
    airEnemyTimer -= GetFrameTime();
    groundEnemyTimer -= GetFrameTime();

    if (airEnemyTimer <= 0)
    {
        obstacles.push_back(new Obstacle(Obstacle::helicopter));
        airEnemyTimer = airOriginalTimer;
        if (airOriginalTimer > 2) airOriginalTimer--;
    }
    if (groundEnemyTimer <= 0)
    {
        obstacles.push_back(new Obstacle(Obstacle::bike));
        groundEnemyTimer = groundOriginalTimer;
        if (groundOriginalTimer > 2) groundOriginalTimer--;
    }
}
