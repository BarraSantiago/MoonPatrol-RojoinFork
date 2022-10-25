#include <ctime>
#include <raylib.h>

#include "statesManager.h"
#include "GameStates.h"
#include "menuState.h"
#include "rulesState.h"
#include "creditsState.h"
#include "initialAnimationScreen.h"
#include "optionsState.h"
#include "system/draw.h"


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

	switch (gameStates)
	{
	case GameStates::InitialAnimation:
		statesInitialAnimation();
		break;
	case GameStates::Menu:
		statesMenu(gameStates);
		break;
	case GameStates::Game:
		//GameLogic::playGame();
		break;
	case GameStates::Rules:
		statesRules();
		break;
	case GameStates::Options:
		statesOptions();
		break;
	case GameStates::Credits:
		statesCredits();
		break;
	case GameStates::Exit:
		isProgramRunning = false;
		break;

	}
}

void drawProgram()
{
	BeginDrawing();
	ClearBackground(BLACK);
	
	switch (gameStates)
	{
	case GameStates::InitialAnimation:
		drawInitialAnimation();
		break;
	case GameStates::Menu:
		drawMenu();
		break;
	case GameStates::Game:
		//GameLogic::drawGame();
		break;
	case GameStates::Rules:
		drawRules();
		break;
	case GameStates::Options:
		drawOptions();
		break;
	case GameStates::Credits:
		drawCredits();
		break;
	case GameStates::Exit:
		break;
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
	//UnloadFont(customFont);
	unLoadAudio();
	unLoadTextures();

}