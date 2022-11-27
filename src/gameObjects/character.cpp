#include "character.h"
#include <iostream>
#include "raylib.h"

Character::Character()
{
    const float initialX = static_cast<float>(GetScreenWidth()) / 2.0f;
    const float initialY = static_cast<float>(GetScreenHeight()) / 2.0f;
    const float initialWidth = static_cast<float>(GetScreenWidth()) / 6.5f;
    const float initialHeight = static_cast<float>(GetScreenWidth()) / 20.0f;
    body = {initialX, initialY, initialWidth, initialHeight};
    hp = 3;
    alive = true;
    jumpState = false;
    speed = static_cast<float>(GetScreenWidth()) / 2.0f;
    gravity = speed;
    floorLevel = GetScreenHeight() * 0.90287f - body.height;
}

Character::~Character()
{
    std::cout << "Character has been destroyed" << std::endl;
}

void Character::reset()
{
    const float initialX = static_cast<float>(GetScreenWidth()) / 2.0f;
    const float initialY = static_cast<float>(GetScreenHeight()) / 2.0f;
    const float initialWidth = static_cast<float>(GetScreenWidth()) / 30.0f;
    const float initialHeight = static_cast<float>(GetScreenWidth()) / 30.0f;
    body = {initialX, initialY, initialWidth, initialHeight};
    alive = true;
    hp = 3;
    jumpState = false;
    gravity = speed;
}


void Character::draw() const
{
    DrawRectangleRec(body, RED);
}

void Character::jump()
{
    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE)) && body.y >= floorLevel) jumpState =
        true;

    if (jumpState)
    {
        static float jumpTimer = 0.4f;
        jumpTimer -= GetFrameTime();
        body.y -= GetFrameTime() * speed * 2.f;
        if (jumpTimer <= 0)
        {
            jumpState = false;
            jumpTimer = 0.4f;
        }
    }
}

void Character::moveRight()
{
    if (IsKeyDown(KEY_D)) body.x += speed * GetFrameTime();
}

void Character::moveLeft()
{
    if (IsKeyDown(KEY_A)) body.x -= speed * GetFrameTime();
}

void Character::update()
{
    jump();
    moveRight();
    moveLeft();
    if (body.y <= floorLevel)
    {
        body.y += GetFrameTime() * gravity / 1.5f;
    }
    else if (body.y > floorLevel)
    {
        body.y = floorLevel;
    }
}


Rectangle Character::getBody() const
{
    return body;
}

bool Character::isAlive() const
{
    return alive;
}

void Character::setHP(int hpModifier)
{
    hp += hpModifier;
    if (hp <= 0)
    {
        alive = false;
    }
}

float Character::getSpeed() const
{
    return speed;
}

void Character::setSpeed(float speed_)
{
    this->speed = speed_;
}
