#include "obstacle.h"

#include <iostream>
#include "raylib.h"

Obstacle::Obstacle()
{
    rec = {1280, 600, 75, 150};
}

Obstacle::~Obstacle()
{
    std::cout << "Character has been destroyed" << std::endl;
}

void Obstacle::reset()
{
    rec = {1280, 600, 75, 150};
}

void Obstacle::changePosX()
{
    rec.x -= 200 * GetFrameTime();
    if (rec.x < 0)
    {
        rec.x = static_cast<float>(GetScreenWidth());
    }
}

void Obstacle::draw() const
{
    DrawRectangle(static_cast<int>(rec.x), static_cast<int>(rec.y), static_cast<int>(rec.width),
                  static_cast<int>(rec.height), BLUE);
}

Rectangle Obstacle::getRec() const
{
    return rec;
}

Circle Obstacle::getBody() const
{
    return body;
}

void Obstacle::setY(float y_)
{
    body.y = y_;
}

void Obstacle::setX(float x_)
{
    body.x = x_;
}
