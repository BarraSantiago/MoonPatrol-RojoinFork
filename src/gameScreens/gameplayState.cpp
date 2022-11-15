#include "gameplayState.h"

#include <iostream>
#include "system/draw.h"
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
float scrollingBack = 0.0f;
float scrollingMid = 0.0f;
float scrollingFore = 0.0f;
void initTextures();
void unloadTextures();
void backToMenu();

void gameLogic()
{
	scrollingBack -= 0.1f* GetFrameTime() * 200.0f;
	scrollingMid -= 0.5f * GetFrameTime() * 200.0f;
	scrollingFore -= 1.0f* GetFrameTime() * 200.0f;

	if (scrollingBack <= -paralaxBackground.width * 2 ) scrollingBack = 0;
	if (scrollingMid <= -paralaxMidground.width * 2) scrollingMid = 0;
	if (scrollingFore <= -paralaxNearForeground.width * 2 ) scrollingFore = 0;

	backToMenu();
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
		firstTime = true;
		unloadTextures();
	}
	character->setPlayerDeadStatus(isCharacterObstacleColliding(character, obstacle));
}

void backToMenu()
{
	if (IsKeyDown(KEY_ESCAPE))
	{
		setGameState(GameStates::Menu);
		character->reset();
		obstacle->reset();
		firstTime = true;
		unloadTextures();
	}
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
	drawTexture(paralaxBackground, { scrollingBack, 0 }, 0.0f, 5.0f, WHITE);
	drawTexture(paralaxBackground, { paralaxBackground.width * 2 + scrollingBack, 0 }, 0.0f, 5.0f, WHITE);

	drawTexture(paralaxMidground, { scrollingMid, 20 }, 0.0f, 4.0f, WHITE);
	drawTexture(paralaxMidground, { paralaxMidground.width * 2 + scrollingMid, 20 }, 0.0f, 4.0f, WHITE);

	character->draw();
	obstacle->draw();
	std::cout << paralaxNearForeground.width * 2 + scrollingFore << std::endl;
	drawTexture(paralaxNearForeground, { scrollingFore, 70 }, 0.0f, 4.0f, WHITE);
	//DrawTextureEx(paralaxNearForeground, { paralaxNearForeground.width * 2 + scrollingFore, 70 }, 0.0f, 4.0f, WHITE);


}
