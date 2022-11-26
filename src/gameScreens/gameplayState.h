#pragma once

#include "gameObjects/Character.h"
#include "gameObjects/Obstacle.h"

class GameplayState
{
private:
    Character* character;
    Obstacle* obstacle;
    Texture2D paralaxBackground;
    Texture2D paralaxMidground;
    Texture2D paralaxForeground;

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;
    float paralaxScale;

    void initTextures();
    void unloadTextures();
    void BackgroundParalax();
    void backToMenu();
public:
    GameplayState();
    ~GameplayState();
    void gameLogic();
    void drawGame();
};
