#include "Bullets.h"
#include "system/draw.h"


Bullet::Bullet(Texture2D texture, Sound sound)
{
    this->texture = texture;
    this->direction = {0, 0};
    this->rotation = 0;
    this->body = {0,0,0};
    this->speed = 0;
    this->active = false;
    this->scale = static_cast<float>(GetScreenHeight()) / 780;
    this->body.radius *= scale;
    this->sound = sound;
}

Bullet::Bullet(Texture2D texture, Sound sound, Vector2 direction, Vector2 position, float radius, float rotation, float speed)
{
    this->texture = texture;
    this->sound = sound;
    this->direction = direction;
    this->rotation = rotation;
    this->body = {position.x, position.y, radius};
    this->speed = speed;
    active = true;
}
void Bullet::changeBulletPosition()
{
    body.x += direction.x * speed * GetFrameTime() * static_cast<float>(GetScreenWidth()) / 1024;
    body.y += direction.y * speed * GetFrameTime() * static_cast<float>(GetScreenHeight()) / 768;
}


void Bullet::drawBullet()
{
    if (active)
    {
        Rectangle source{0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
        Rectangle dest{
            body.x, body.y, static_cast<float>(texture.width) * scale, static_cast<float>(texture.height) * scale
        };

#if _DEBUG

        DrawCircle(static_cast<int>(body.x), static_cast<int>(body.y), body.radius, BLUE);
#endif
        
        drawTexture(texture, source, dest, {
                        static_cast<float>(texture.width) / 2.0f, static_cast<float>(texture.height) / 2.0f},
                        rotation, scale, WHITE);
    }
}

Circle Bullet::getBody() const
{
    return body;
}

void Bullet::setActive(bool active_)
{
    this->active = active_;
}

bool Bullet::isActive()
{
    return active;
}
