#include "Bullets.h"
#include "system/draw.h"

Sound bulletDefaultSound;
Sound bulletSniperSound;
Sound bulletPiercingSound;
Texture bulletTexture;
Texture bulletPiercingTexture;
Texture bulletSniperTexture;


Bullet::Bullet(float x, float y, Texture2D texture)
{
    this->texture = texture;
    this->isActive = false;
    this->aceleration = {0, 0};
    this->circle = {x, y, 10};
    this->rotation = 0;
    this->speed = 300;
    this->scale = 1.0f * static_cast<float>(GetScreenHeight()) / 768;
    this->sound = bulletDefaultSound;
    this->texture = bulletTexture;
    this->circle.radius *= scale;
}

void Bullet::changeBulletPosition()
{
    circle.x += aceleration.x * speed * GetFrameTime() * static_cast<float>(
        GetScreenWidth()) / 1024;
    circle.y += aceleration.y * speed * GetFrameTime() * static_cast<float>(
        GetScreenHeight()) / 768;
}


void Bullet::drawBullet()
{
    if (isActive)
    {
        Rectangle source{0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
        Rectangle dest{
            circle.x, circle.y, static_cast<float>(texture.width) * scale, static_cast<float>(texture.height) * scale
        };

#if _DEBUG

        //DrawCircle(static_cast<int>(circle.x), static_cast<int>(circle.y), circle.radius, BLUE);
#endif
        drawTexture(texture, source, dest, {
                        static_cast<float>(texture.width) / 2.0f,
                        static_cast<float>(texture.height) / 2.0f
                    }, rotation, scale, WHITE);
    }
}
