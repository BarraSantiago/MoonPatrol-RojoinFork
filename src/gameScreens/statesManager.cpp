#include <ctime>
#include <raylib.h>

#include "statesManager.h"
#include "system/draw.h"
#include "gameStatesEnum.h"
#include "menu/rulesState.h"
#include "gameScreens/menu/menuState.h"
#include "gameScreens/gameplayState.h"
#include "gameScreens/menu/optionsState.h"
#include "gameScreens/menu/creditsState.h"


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

static GameplayState* gameplayState;

void initProgram()
{
    setGameState(GameStates::Menu);
    SetRandomSeed(static_cast<unsigned int>(time(nullptr)));
    InitWindow(1600, 900, "Mad Patrol");
    InitAudioDevice();
    loadResources();
    SetExitKey(NULL);
    SetWindowSize(1600, 900);


    isProgramRunning = true;
    gameplayState = new GameplayState;
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
        gameplayState->gameLogic();
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
    default: ;
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
        gameplayState->drawGame();
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
    default: ;
    }

    const int fontSize = (GetScreenWidth()) / 40;
    const int textX = (GetScreenWidth()) / 50;
    const int textY = static_cast<int>(GetScreenHeight() * 0.95f);
    drawText("Version:1.0", textX, textY, fontSize, RAYWHITE);
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

void unLoadResources()
{
    unLoadAudio();
    unLoadTextures();
}

void unLoadAudio()
{
}

void unLoadTextures()
{
}
