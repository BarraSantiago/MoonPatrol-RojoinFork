#pragma once
#include "raylib.h"
#include "system/circle.h"

class Obstacle
{
private:
    Rectangle rec;
    Circle body;
public:
    Obstacle();
    ~Obstacle();
    void reset();
    void changePosX();
    void draw() const;
    Rectangle getRec() const;
    Circle getBody() const;
    void setY(float y_);
    void setX(float x_);
};
