#pragma once
#include "raylib.h"
#include "system/circle.h"

class Obstacle
{
public:
    enum EnemyType
    {
        bike,
        truck,
        helicopter
    };
    Obstacle();
    ~Obstacle();
    void reset();
    void changePosX();
    void SinusoidalMovement();
    void draw() const;
    Circle getBody() const;
    void modifyHP(int hpModifier);
    bool isAlive();
    void setY(float y_);
    void setX(float x_);
private:
    Circle body;
    bool alive;
    int hp;
    EnemyType type;

};
