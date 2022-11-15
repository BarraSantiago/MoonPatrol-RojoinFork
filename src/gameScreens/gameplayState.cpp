#include "gameplayState.h"

#include "gameLogic/gameLogic.h"
#include "gameObjects/Character.h"
#include "gameObjects/Obstacle.h"
#include "gameScreens/gameStatesEnum.h"

Character* character = new Character();
Obstacle* obstacle = new Obstacle();

bool firstTime = true;
Texture2D paralaxBackground;
Texture2D paralaxMidground;
Texture2D paralaxNearForeground;

void initTextures();

void gameLogic()
{
	if (firstTime)
	{
		initTextures();
		firstTime = false;
	}
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
		firstTime = false;
		void unloadTextures();
	}
	character->setPlayerDeadStatus(isCharacterObstacleColliding(character, obstacle));
}

void initTextures()
{
	paralaxBackground = LoadTexture("res/parallax-mountain-bg.png");
	paralaxMidground = LoadTexture("res/parallax-mountain-mountains.png");
	paralaxNearForeground = LoadTexture("res/parallax-mountain-foreground-trees.png");
}

void unloadTextures()
{
	UnloadTexture(paralaxBackground);
	UnloadTexture(paralaxMidground);
	UnloadTexture(paralaxNearForeground);
}
void drawGame()
{
	character->draw();
	obstacle->draw();
}
