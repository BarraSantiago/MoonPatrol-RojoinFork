#include "gameLogic.h"

bool isCharacterObstacleColliding(Character* character, Obstacle* obstacle)
{
    return isCircleCircleColliding(character->getBody(), obstacle->getBody());
}
