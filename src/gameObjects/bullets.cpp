#include "Bullets.h"
#include "system/draw.h"

Sound bulletDefaultSound;
Sound bulletSniperSound;
Sound bulletPiercingSound;
Texture bulletTexture;
Texture bulletPiercingTexture;
Texture bulletSniperTexture;

namespace GameObjects
{
    Bullet createBullet(float x, float y)
    {
        Bullet bullet;
        bullet.isActive = false;
        bullet.aceleration = {0, 0};
        bullet.circle = {x, y, 10};
        bullet.rotation = 0;
        bullet.speed = 300;
        bullet.scale = 1.0f * static_cast<float>(GetScreenHeight()) / 768;
        bullet.sound = bulletDefaultSound;
        bullet.texture = bulletTexture;
        bullet.circle.radius *= bullet.scale;
        return bullet;
    }

    void changeBulletPosition(Bullet& bullet)
    {
        bullet.circle.x += bullet.aceleration.x * bullet.speed * GetFrameTime() * static_cast<float>(
            GetScreenWidth()) / 1024;
        bullet.circle.y += bullet.aceleration.y * bullet.speed * GetFrameTime() * static_cast<float>(
            GetScreenHeight()) / 768;
    }


    void drawBullet(Bullet& bullet)
    {
        if (bullet.isActive)
        {
            Rectangle source{0, 0, static_cast<float>(bullet.texture.width), static_cast<float>(bullet.texture.height)};
            Rectangle dest{
                bullet.circle.x, bullet.circle.y,
                static_cast<float>(bullet.texture.width) * bullet.scale,
                static_cast<float>(bullet.texture.height) * bullet.scale
            };

#if _DEBUG

            //DrawCircle(static_cast<int>(bullet.circle.x), static_cast<int>(bullet.circle.y), bullet.circle.radius, BLUE);
#endif
            drawTexture(bullet.texture, source, dest, {
                            static_cast<float>(bullet.texture.width) / 2.0f,
                            static_cast<float>(bullet.texture.height) / 2.0f
                        }, bullet.rotation, bullet.scale, WHITE);
        }
    }
}
