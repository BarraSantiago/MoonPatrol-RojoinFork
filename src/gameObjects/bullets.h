#pragma once
#include <raylib.h>
#include "system/circle.h"

class Bullet
{
    
private:
    Texture texture;
    Circle body;
    Vector2 direction;
    Sound sound;
    float rotation;
    bool active;
    float scale;
    float speed;
    int maxBullets = 20;
public:
    Bullet(Texture2D texture, Sound sound);
    Bullet(Texture2D texture, Sound sound, Vector2 direction, Vector2 position, float radius, float rotation, float speed);
    void changeBulletPosition();
    void drawBullet();
    Circle getBody() const;
    void setActive(bool active_);
    bool isActive();
    float BULLET_MAX_SPEED = 500.0f;

};

