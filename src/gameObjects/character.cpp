#include "character.h"
#include <iostream>
#include "raylib.h"

Character::Character()
{
    const float initialX = static_cast<float>(GetScreenWidth()) / 2.0f;
    const float initialY = static_cast<float>(GetScreenHeight()) / 2.0f;
    const float initialRadius = static_cast<float>(GetScreenWidth()) / 30.0f;
    body = {initialX, initialY, initialRadius};
    hp = 3;
    alive = true;
    jumpState = false;
    gravity = 200.0f;
}

Character::~Character()
{
    std::cout << "Character has been destroyed" << std::endl;
}

void Character::reset()
{
    const float initialX = static_cast<float>(GetScreenWidth()) / 2.0f;
    const float initialY = static_cast<float>(GetScreenHeight()) / 2.0f;
    const float initialRadius = static_cast<float>(GetScreenWidth()) / 30.0f;
    body = {initialX, initialY, initialRadius};
    alive = true;
    hp = 3;
    jumpState = false;
    gravity = 200.0f;
}


void Character::draw() const
{
    DrawCircle(static_cast<int>(body.x), static_cast<int>(body.y), body.radius, RED);
}

void Character::jump()
{
    jumpState = ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && body.y >= 600.0f);

    if (jumpState)
    {
        static float jumpTimer = 0.8f;
        jumpTimer -= GetFrameTime();
        body.y += GetFrameTime() * -gravity * 1.5f;
        if (jumpTimer <= 0)
        {
            jumpState = false;
            jumpTimer = 0.8f;
        }
    }
}

void Character::update()
{
    jump();
    if (body.y <= 600.0f)
    {
        body.y += GetFrameTime() * gravity;
    }
    else if (body.y > 600.0f)
    {
        body.y = 600.0f;
    }
}


Circle Character::getBody() const
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
