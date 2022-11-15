#include <ctime>
#include <raylib.h>

#include "statesManager.h"
#include "system/draw.h"
#include "gameStatesEnum.h"
#include "rulesState.h"
#include "gameScreens/menuState.h"
#include "gameScreens/gameplayState.h"
#include "gameScreens/optionsState.h"
#include "gameScreens/creditsState.h"



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
	setGameState(GameStates::Menu);
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
		break;
	case GameStates::Menu:
		statesMenu(gameStates);
		break;
	case GameStates::Game:
		gameLogic();
		break;
	case GameStates::Rules:
		statesRules();
		break;
	case GameStates::Options:
		break;
	case GameStates::Credits:
		statesCredits();
		break;
	case GameStates::Exit:
		isProgramRunning = false;
		break;
	default:;
	}

}

void drawProgram()
{
	BeginDrawing();
	ClearBackground(BLACK);
	switch (gameStates)
	{
	case GameStates::InitialAnimation:
		break;
	case GameStates::Menu:
		drawMenu();
		break;
	case GameStates::Game:
		drawGame();
		break;
	case GameStates::Rules:
		drawRules();
		break;
	case GameStates::Options:
		break;
	case GameStates::Credits:
		drawCredits();
		break;
	case GameStates::Exit:
		break;
	default:;
	}

	drawText("Version:0.2", 720, 720, 40, RAYWHITE);
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
