#include "Character.h"

#include <iostream>

#include "raylib.h"
#include "system/draw.h"

Character::Character()
{
    body = {200.0f, 600.0f, 50};
    hp = 3;
    alive = false;
    jumpState = false;
    gravity = 200.0f;
}

Character::~Character()
{
    std::cout << "Character has been destroyed" <<std::endl;
}

void Character::reset()
{
    body = {200.0f, 600.0f, 50};
    alive = false;
    jumpState = false;
    gravity = 200.0f;
}

void Character::changePos()
{
    if (IsKeyPressed(KEY_UP) && body.y >= 600.0f)
    {
        jump();
    }
}

void Character::draw()
{
    DrawRectangle(static_cast<int>(body.x), static_cast<int>(body.y), static_cast<int>(body.radius),
                  static_cast<int>(body.radius), RED);
}

void Character::update()
{
    static float jumpTimer = 0.8f;

    if (jumpState)
    {
        jumpTimer -= GetFrameTime();
        body.y += GetFrameTime() * -gravity;
        if (jumpTimer <= 0)
        {
            jumpState = false;
            jumpTimer = 0.8f;
        }
    }
    else if (body.y <= 600.0f)
    {
        body.y += GetFrameTime() * gravity;
    }
    else if (body.y > 600.0f)
    {
        body.y = 600.0f;
    }
}

void Character::jump()
{
    jumpState = true;
}

Circle Character::GetBody() const
{
    return body;
}

bool Character::isAlive() const
{
    return alive;
}

void Character::SetHitPoints(int hpModifier)
{
    hp += hpModifier;
    if (hp <= 0)
    {
        alive = false;
    }
}
