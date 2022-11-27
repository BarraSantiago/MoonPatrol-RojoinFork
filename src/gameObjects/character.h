#pragma once
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
public:
    Character();
    ~Character();
    void reset();
    void draw() const;
    void update();
    void jump();
    void moveRight();
    void moveLeft();
    Rectangle getBody() const;
    bool isAlive() const;
    void setHP(int hpModifier);
    float getSpeed() const;
    void setSpeed(float speed_);
};
