#include "gameplayState.h"

#include <iostream>
#include "system/draw.h"
#include "gameLogic/gameLogic.h"
#include "gameScreens/gameStatesEnum.h"

static bool firstTime = true;

GameplayState::GameplayState()
{
    character = new Character;
    obstacle = new Obstacle;
    paralaxScale = 0.7f;
    initTextures();
    initAudios();
}

GameplayState::~GameplayState()
{
    for (Bullet* bullet : bullets)
    {
        delete bullet;
    }
    delete character;
    delete obstacle;
    std::cout << "Gameplay state has been destroyed.";
}

void GameplayState::gameLogic()
{
    backToMenu();

    if (character->isAlive())
    {
        update();
    }
    else
    {
        setGameState(GameStates::Menu);
        character->reset();
        obstacle->reset();
        firstTime = true;
        unloadTextures();
    }
}

void GameplayState::backToMenu()
{
    if (IsKeyDown(KEY_ESCAPE))
    {
        setGameState(GameStates::Menu);
        character->reset();
        obstacle->reset();
        firstTime = true;
        unloadTextures();
    }
}


void GameplayState::update()
{
    obstacle->changePosX();
    character->update();

    if (IsKeyReleased(KEY_W)) bullets.push_back(character->shootUp(characterBullet, bulletSound));
    if (IsKeyReleased(KEY_F)) bullets.push_back(character->shootRight(characterBullet, bulletSound));

    for (Bullet* bullet : bullets)
    {
        bullet->changeBulletPosition();
    }

    //if (isCharacterObstacleColliding(character, obstacle)) character->setHP(-1);

    for (Bullet* bullet : bullets)
    {
        if (obstacle->isAlive() && bullet->isActive())
        {
            if (isObstacleBulletColliding(obstacle, bullet))
            {
                bullet->setActive(false);
                obstacle->modifyHP(-1);
            }
        }
    }

    wheelRotation += GetFrameTime() * character->getSpeed();
    BackgroundParalax();
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
}

void GameplayState::drawBackground() const
{
    static float rotation = 0;
    drawTexture(paralaxBackground, {scrollingBack, 0}, rotation, paralaxScale, WHITE);
    drawTexture(paralaxBackground, {paralaxBackground.width * paralaxScale + scrollingBack, 0}, rotation, paralaxScale,
                WHITE);

    drawTexture(paralaxMidground, {scrollingMid, 0}, rotation, paralaxScale, WHITE);
    drawTexture(paralaxMidground, {paralaxMidground.width * paralaxScale + scrollingMid, 0}, rotation, paralaxScale,
                WHITE);
}

void GameplayState::drawForeground() const
{
    static float rotation = 0;

    drawCharacter();
    drawObstacles();
    if (obstacle->isAlive()) obstacle->draw();
    for (Bullet* bullet : bullets)
    {
        bullet->drawBullet();
    }
    drawTexture(paralaxForeground, {scrollingFore, 0}, rotation, paralaxScale, WHITE);
    drawTexture(paralaxForeground, {paralaxForeground.width * paralaxScale + scrollingFore, 0}, rotation,
                paralaxScale, WHITE);
}

void GameplayState::drawCharacter() const
{
    drawTexture(characterVehicle, {
                    character->getBody().x - characterVehicle.width / 4.3f,
                    character->getBody().y - characterVehicle.height / 1.2f
                }, 0, 2, RAYWHITE);

    const Vector2 origin = {10, 10};

    DrawTexturePro(characterWheel,
                   {0, 0, static_cast<float>(characterWheel.width), static_cast<float>(characterWheel.height)},
                   {
                       character->getBody().x + characterVehicle.width * 1.5f,
                       character->getBody().y + characterVehicle.height * 1.5f, 50, 50
                   }, origin, wheelRotation,
                   RAYWHITE);

    //character->draw();
}

void GameplayState::drawObstacles() const
{
    if (obstacle->isAlive())
    {
        drawTexture(obstacleBike, {
                        obstacle->getBody().x - obstacleBike.width / 4.3f,
                        obstacle->getBody().y - obstacleBike.height / 2.f
                    }, 0, 2, RAYWHITE);
    }
}

void GameplayState::BackgroundParalax()
{
    const float paralaxSpeed = character->getSpeed() / 2;
    scrollingBack -= 0.1f * GetFrameTime() * paralaxSpeed;
    scrollingMid -= 0.5f * GetFrameTime() * paralaxSpeed;
    scrollingFore -= 1.0f * GetFrameTime() * paralaxSpeed;

    if (scrollingBack <= -paralaxBackground.width * paralaxScale) scrollingBack = 0;
    if (scrollingMid <= -paralaxMidground.width * paralaxScale) scrollingMid = 0;
    if (scrollingFore <= -paralaxForeground.width * paralaxScale) scrollingFore = 0;
}
