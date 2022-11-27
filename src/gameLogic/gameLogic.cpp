#include "gameLogic.h"

bool isCharacterObstacleColliding(Character* character, Obstacle* obstacle)
{
    return isCircleRectColliding( obstacle->getBody(), character->getBody());
}
