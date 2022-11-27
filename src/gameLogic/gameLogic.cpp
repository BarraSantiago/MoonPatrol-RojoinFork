#include "gameLogic.h"

#include "system/collisionFunctions.h"

bool isCharacterObstacleColliding(Character* character, Obstacle* obstacle)
{
    return isCircleRectColliding( obstacle->getBody(), character->getBody());
}

bool isObstacleBulletColliding(Obstacle* obstacle, Bullet* bullet)
{
    return isCircleCircleColliding(obstacle->getBody(), bullet->getBody());
}