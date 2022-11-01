#include <ctime>
#include <raylib.h>

#include "statesManager.h"
#include "system/draw.h"
#include "gameStates.h"
#include "gameObjects/Character.h"
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
	 character->changePos();
	
}

void drawProgram()
{
	BeginDrawing();
	ClearBackground(BLACK);
	
	character->drawCharacter();
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