#pragma once
#include <raylib.h>
#include "system/circle.h"

class Bullet
{
    
private:
    Texture texture;
    Circle circle;
    Vector2 aceleration;
    Sound sound;
    float rotation;
    bool isActive;
    float scale;
    float speed;
    int maxBullets = 20;
public:
    Bullet(float x, float y, Texture2D texture);
    void changeBulletPosition();
    void drawBullet();
    float BULLET_MAX_SPEED = 500.0f;

};
