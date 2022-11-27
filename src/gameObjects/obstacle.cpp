#include "obstacle.h"

#include <iostream>
#include "raylib.h"

Obstacle::Obstacle()
{
    speed = 200.f;
    hp = 2;
    alive = true;
    const float initialX = static_cast<float>(GetScreenWidth()) / 2.0f;
    const float initialRadius = static_cast<float>(GetScreenWidth()) / 20.f;
    const float initialY = GetScreenHeight() * 0.90287f - initialRadius;
    body = {initialX, initialY, initialRadius};
}

Obstacle::Obstacle(EnemyType type)
{
    speed = 200.f;
    hp = 2;
    alive = true;
    this->type = type;

    const float initialX = static_cast<float>(GetScreenWidth()) * .99f;
    const float initialRadius = static_cast<float>(GetScreenWidth()) / 20.f;

    float initialY;

    switch (type)
    {
    case bike:
        initialY = static_cast<float>(GetScreenHeight()) * 0.90287f - initialRadius;
        break;
    case helicopter:
        initialY = static_cast<float>(GetScreenHeight()) / 6.f;
        break;
    case truck:
    default:
        initialY = static_cast<float>(GetScreenHeight()) * 0.90287f - initialRadius;
    }

    body = {initialX, initialY, initialRadius};
}

Obstacle::~Obstacle()
{
    std::cout << "Character has been destroyed" << std::endl;
}

void Obstacle::reset()
{
    const float initialX = static_cast<float>(GetScreenWidth()) / 2.0f;
    const float initialY = static_cast<float>(GetScreenHeight()) / 2.0f;
    const float initialWidth = static_cast<float>(GetScreenWidth()) / 20.f;
    body = {initialX, initialY, initialWidth};
}

void Obstacle::move()
{
    if (type == helicopter)
    {
        body.x += speed * GetFrameTime();
        if (getBody().x > GetScreenWidth())
        {
            body.x = 0;
        }
        SinusoidalMovement();
    }
    else
    {
        body.x -= speed * GetFrameTime();
        if (body.x < 0)
        {
            body.x = static_cast<float>(GetScreenWidth());
        }
    }
}

void Obstacle::SinusoidalMovement()
{
    body.y += sin(body.x / 16) * GetFrameTime() * static_cast<float>(GetScreenWidth()) / 2;
}

void Obstacle::draw() const
{
    DrawCircle(static_cast<int>(body.x), static_cast<int>(body.y), body.radius,BLUE);
}


Circle Obstacle::getBody() const
{
    return body;
}

Obstacle::EnemyType Obstacle::getType() const
{
    return type;
}

void Obstacle::modifyHP(int hpModifier)
{
    hp += hpModifier;
    if (hp <= 0)
    {
        alive = false;
    }
}

bool Obstacle::isAlive()
{
    return alive;
}

void Obstacle::setY(float y_)
{
    body.y = y_;
}

void Obstacle::setX(float x_)
{
    body.x = x_;
}
