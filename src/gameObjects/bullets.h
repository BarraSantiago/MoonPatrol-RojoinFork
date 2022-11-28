#pragma once
#include <raylib.h>
#include "system/circle.h"

class Bullet
{
    
private:
    Texture texture;
    Circle body;
    Vector2 direction;
    float rotation;
    bool active;
    float speed;
    int maxBullets = 20;
public:
    Bullet(Texture2D texture);
    Bullet(Texture2D texture, Vector2 direction, Vector2 position, float radius, float rotation, float speed);
    void changeBulletPosition();
    void drawBullet();
    Circle getBody() const;
    void setActive(bool active_);
    bool isActive() const;
    float BULLET_MAX_SPEED = 500.0f;

};

