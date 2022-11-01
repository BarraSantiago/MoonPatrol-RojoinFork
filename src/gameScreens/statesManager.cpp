#include <ctime>
#include <raylib.h>

#include "statesManager.h"
#include "system/draw.h"
#include "gameStates.h"
#include "gameObjects/Character.h"
#include "gameObjects/Obstacle.h"
#include "gameLogic/gameLogic.h"

GameStates gameStates;

Music mainTheme;
bool isProgramRunning = true;

int mousePosX;
int mousePosY;
 void logicProgram();
 void drawProgram();
 void loadResources();
 void unLoadResources();
 void loadTextures();
 void unLoadTextures();
 void unLoadAudio();
 void loadAudios();
 
 Character* character = new Character();
 Obstacle* obstacle = new Obstacle();

void initProgram()
{
	setGameState(GameStates::InitialAnimation);
	SetRandomSeed(static_cast<unsigned int>(time(NULL)));
	InitWindow(1024, 768, "MoonPatrol");
	InitAudioDevice();
	loadResources();
	SetExitKey(NULL);
	SetWindowMinSize(1024, 768);

	isProgramRunning = true;

	while (!WindowShouldClose() && isProgramRunning)
	{
		UpdateMusicStream(mainTheme);

		logicProgram();

		drawProgram();
	}
	unLoadResources();
	CloseWindow();
	CloseAudioDevice();
}

 void logicProgram()
{
	 if (character->isPlayerDead() != true)
	 {
	 character->changePos();
	 obstacle->changePosX();

	 }
	 character->setPlayerDeadStatus(isCharacterObstacleColliding(character,obstacle));
}

void drawProgram()
{
	BeginDrawing();
	ClearBackground(BLACK);
	
	if (!character->isPlayerDead())
	{
		character->drawCharacter();
	obstacle->draw();
	}
	else
	{
		drawText("GameOver", 720, 720, 40, RED);
	}
	EndDrawing();
}

void loadAudios()
{

}

 void loadTextures()
{

}

 void loadResources()
{

}

void unLoadAudio()
{

}
 void unLoadTextures()
{
	
}

void unLoadResources()
{
	unLoadAudio();
	unLoadTextures();

}
