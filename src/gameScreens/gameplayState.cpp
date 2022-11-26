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
    character->setHP(isCharacterObstacleColliding(character, obstacle) ? -1 : 0);
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
    paralaxBackground = LoadTexture("res/montain_bakground.png");
    paralaxMidground = LoadTexture("res/mountain_midground.png");
    paralaxForeground = LoadTexture("res/mountain_foreground.png");
}

void GameplayState::unloadTextures()
{
    UnloadTexture(paralaxBackground);
    UnloadTexture(paralaxMidground);
    UnloadTexture(paralaxForeground);
}

void GameplayState::drawGame()
{
    static float rotation = 0;
    drawTexture(paralaxBackground, {scrollingBack, 0}, rotation, paralaxScale, WHITE);
    drawTexture(paralaxBackground, {paralaxBackground.width * paralaxScale + scrollingBack, 0}, rotation, paralaxScale,
                WHITE);

    drawTexture(paralaxMidground, {scrollingMid, 0}, rotation, paralaxScale, WHITE);
    drawTexture(paralaxMidground, {paralaxMidground.width * paralaxScale + scrollingMid, 0}, rotation, paralaxScale,
                WHITE);

    character->draw();
    obstacle->draw();
    drawTexture(paralaxForeground, {scrollingFore, 0}, rotation, paralaxScale, WHITE);
    DrawTextureEx(paralaxForeground, {paralaxForeground.width * paralaxScale + scrollingFore, 0}, rotation,
                  paralaxScale, WHITE);
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
