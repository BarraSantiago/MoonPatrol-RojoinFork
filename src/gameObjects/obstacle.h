#pragma once
#include "raylib.h"
#include "system/circle.h"

class Obstacle
{
public:
    
    enum EnemyType
    {
        bike,
        helicopter,
        truck
    };
    
    Obstacle();
    Obstacle(EnemyType type);
    ~Obstacle();
    void reset();
    void move();
    void SinusoidalMovement();
    void draw() const;
    Circle getBody() const;
    EnemyType getType() const;
    void modifyHP(int hpModifier);
    bool isAlive();
    void setY(float y_);
    void setX(float x_);
    
private:
    
    float speed;
    Circle body;
    bool alive;
    int hp;
    EnemyType type;

};
