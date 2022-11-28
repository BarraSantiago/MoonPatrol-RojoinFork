#pragma once

#include <vector>
#include "gameObjects/Bullets.h"
#include "gameObjects/Character.h"
#include "gameObjects/Obstacle.h"

class GameplayState
{
private:
    Character* characterP1;
    Character* characterP2;
    std::vector<Obstacle*> obstacles;
    std::vector<Bullet*> bullets;
    
    Texture2D paralaxBackground;
    Texture2D paralaxMidground;
    Texture2D paralaxForeground;
    Texture2D characterP1Vehicle;
    Texture2D characterP2Vehicle;
    Texture2D characterWheel;
    Texture2D characterBullet;
    Texture2D obstacleBike;
    Texture2D obstacleHelicopter;

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;
    float wheelRotation = 0;
    float airEnemyTimer=0;
    float groundEnemyTimer=0;
    float airOriginalTimer = 7;
    float groundOriginalTimer = 4;
    
    void spawnEnemies();
    void checkPlayerTextures();
    void update();
    void bulletBehaviour();
    void initTextures();
    void unloadTextures();
    void drawBackground() const;
    void drawForeground() const;
    void drawCharacter() const;
    void drawObstacles() const;
    void drawGUI() const;
    void BackgroundParalax();
    void backToMenu();
public:
    GameplayState();
    ~GameplayState();
    void gameLogic();
    void drawGame();
};
