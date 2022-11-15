#include "gameplayState.h"

#include "gameLogic/gameLogic.h"
#include "gameObjects/Character.h"
#include "gameObjects/Obstacle.h"
#include "gameScreens/gameStatesEnum.h"

Character* character = new Character();
Obstacle* obstacle = new Obstacle();

Texture2D paralaxBackground;
Texture2D paralaxMidground;
Texture2D paralaxNearForeground;

void gameLogic()
{
	if (character->isPlayerDead() != true)
	{
		character->changePos();
		obstacle->changePosX();
		character->update();
	}
	else
	{
		setGameState(GameStates::Menu);
		character->reset();
		obstacle->reset();
	}
	character->setPlayerDeadStatus(isCharacterObstacleColliding(character, obstacle));
}

void initTextures()
{
	paralaxBackground = LoadTexture("res/parallax-mountain-bg.png");
	paralaxMidground = LoadTexture("res/parallax-mountain-mountains.png");
	paralaxMidground = LoadTexture("res/parallax-mountain-foreground-trees.png");
}


void drawGame()
{
	character->draw();
	obstacle->draw();
}
