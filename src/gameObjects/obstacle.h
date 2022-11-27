#pragma once
#include "raylib.h"
#include "system/circle.h"

class Obstacle
{
private:
    Rectangle rec;
    Circle body;
    bool alive;
    int hp;
public:
    Obstacle();
    ~Obstacle();
    void reset();
    void changePosX();
    void SinusoidalMovement();
    void draw() const;
    Rectangle getRec() const;
    Circle getBody() const;
    void modifyHP(int hpModifier);
    bool isAlive();
    void setY(float y_);
    void setX(float x_);
};
