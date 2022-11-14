#include "gameplayState.h"

#include "gameLogic/gameLogic.h"
#include "gameObjects/Character.h"
#include "gameObjects/Obstacle.h"
#include "gameScreens/gameStatesEnum.h"

Character* character = new Character();
Obstacle* obstacle = new Obstacle();
void gameLogic()
{
	if (character->isPlayerDead() != true)
	{
		character->changePos();
		obstacle->changePosX();

	}
	else
	{
		setGameState(GameStates::Menu);
	}
	character->setPlayerDeadStatus(isCharacterObstacleColliding(character, obstacle));
}

void drawGame()
{
	character->draw();
	obstacle->draw();
}
