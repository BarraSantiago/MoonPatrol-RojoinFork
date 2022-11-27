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
    score = 0;
    speed = static_cast<float>(GetScreenWidth()) / 2.0f;
    gravity = speed;
    floorLevel = static_cast<float>(GetScreenHeight()) * 0.90287f - body.height;
    damagedTimer = 0;
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
    static float jumpTimer = 0.3f;
    if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE)) && body.y >= floorLevel)
    {
        jumpState = true;
        jumpTimer = 0.3f;
        body.y -= speed * GetFrameTime() * 1.5f;
    }

    if (IsKeyDown(KEY_SPACE) && jumpState)
    {
        if (jumpTimer > 0)
        {
            body.y -= speed * GetFrameTime() * 2.f;
            jumpTimer -= GetFrameTime();
        }
        else
        {
            jumpState = false;
        }
    }

    if (IsKeyUp(KEY_SPACE))
    {
        jumpState = false;
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

Bullet* Character::shootUp(Texture2D texture, Sound sound) const
{
    const float size = static_cast<float>(GetScreenWidth()) / 90.0f;
    const float bulletSpeed = speed * 1.3f;
    return new Bullet(texture, sound, {0, -1}, {body.x + body.width / 2, body.y}, size, 90.f, bulletSpeed);
}

Bullet* Character::shootRight(Texture2D texture, Sound sound) const
{
    const float size = static_cast<float>(GetScreenWidth()) / 90.0f;
    const float bulletSpeed = speed * 1.3f;
    return new Bullet(texture, sound, {1, 0}, {body.x + body.width / 2, body.y}, size, 0.f, bulletSpeed);
}

void Character::update()
{
    jump();
    moveRight();
    moveLeft();
    damagedTimer -= GetFrameTime();
    if (body.y < floorLevel)
    {
        body.y += GetFrameTime() * gravity / 1.4f;
    }
    else
    {
        body.y = floorLevel;
    }
}


Rectangle Character::getBody() const
{
    return body;
}

int Character::getScore() const
{
    return score;
}

void Character::addScore(int scoreModifier)
{
    score += scoreModifier;
}

bool Character::isAlive() const
{
    return alive;
}

void Character::setHP(int hpModifier)
{
    if (damagedTimer <= 0 || hpModifier > 0)
    {
        hp += hpModifier;
        if (hpModifier < 0) damagedTimer = 2;
    }
    if (hp <= 0)
    {
        alive = false;
    }
}

float Character::getSpeed() const
{
    return speed;
}

int Character::getHP() const
{
    return hp;
}

void Character::setSpeed(float speed_)
{
    this->speed = speed_;
}
