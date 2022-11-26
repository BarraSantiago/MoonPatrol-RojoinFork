#pragma once
#include "system/circle.h"

class Character
{
private:
    Circle body{};
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
    Circle getBody() const;
    bool isAlive() const;
    void setHP(int hpModifier);
    float getSpeed() const;
    void setSpeed(float speed_);
};
