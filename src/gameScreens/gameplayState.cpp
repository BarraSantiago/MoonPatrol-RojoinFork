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
}

GameplayState::~GameplayState()
{
    std::cout << "Gameplay state has been destroyed.";
}

void GameplayState::gameLogic()
{
    backToMenu();

    if (character->isAlive())
    {
        obstacle->changePosX();
        character->update();
        wheelRotation += GetFrameTime() * character->getSpeed();
        BackgroundParalax();
    }
    else
    {
        setGameState(GameStates::Menu);
        character->reset();
        obstacle->reset();
        firstTime = true;
        unloadTextures();
    }
    //if(isCharacterObstacleColliding(character, obstacle)) character->setHP(-1);
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


void GameplayState::initTextures()
{
    characterVehicle = LoadTexture("res/entities/player_car.png");
    characterWheel = LoadTexture("res/entities/wheel1.png");
    obstacleBike = LoadTexture("res/entities/enemy_bike.png");
    paralaxBackground = LoadTexture("res/montain_bakground.png");
    paralaxMidground = LoadTexture("res/mountain_midground.png");
    paralaxForeground = LoadTexture("res/mountain_foreground.png");
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

    drawCharacter();
    drawObstacles();
    obstacle->draw();
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
    drawTexture(obstacleBike, {
                    obstacle->getBody().x - obstacleBike.width / 4.3f,
                    obstacle->getBody().y - obstacleBike.height / 1.2f
                }, 0, 2, RAYWHITE);

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
