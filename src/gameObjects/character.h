#pragma once
#include "Bullets.h"
#include "system/circle.h"

class Character
{
private:
    Rectangle body{};
    bool alive;
    bool jumpState;
    float gravity;
    float speed;
    int hp;
    float floorLevel;
    int score;
    float damagedTimer;
public:
    Character();
    ~Character();
    void reset();
    void draw() const;
    void update();
    void jump();
    void moveRight();
    void moveLeft();
    Bullet* shootUp(Texture2D texture, Sound sound) const;
    Bullet* shootRight(Texture2D texture, Sound sound) const;

    Rectangle getBody() const;
    int getScore() const;
    bool isAlive() const;
    float getSpeed() const;
    int getHP() const;
    void addScore(int scoreModifier);
    void setSpeed(float speed_);
    void setHP(int hpModifier);
    
};
