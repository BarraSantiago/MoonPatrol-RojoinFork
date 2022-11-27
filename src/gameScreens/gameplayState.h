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
    Texture2D characterVehicle;
    Texture2D characterWheel;
    Texture2D obstacleBike;

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;
    float paralaxScale;
    float wheelRotation = 0;

    void initTextures();
    void unloadTextures();
    void drawBackground() const;
    void drawCharacter() const;
    void drawObstacles() const;
    void BackgroundParalax();
    void backToMenu();
public:
    GameplayState();
    ~GameplayState();
    void gameLogic();
    void drawGame();
};
