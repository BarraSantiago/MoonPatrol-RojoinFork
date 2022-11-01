#include "gameLogic.h"

bool isCharacterObstacleColliding(Character* character, Obstacle* obstacle)
{
	if (isRecRecColliding(character->getRec(),obstacle->getRec()))
	{
		return true;
	}
	return false;
}
