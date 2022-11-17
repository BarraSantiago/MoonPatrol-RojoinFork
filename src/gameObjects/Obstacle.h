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
    Circle GetBody() const;
    void SetY(float y_);
    void SetX(float x_);
};
