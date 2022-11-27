#include <string>

#include "../button.h"
#include "../gameStatesEnum.h"
#include "menuState.h"
#include "raylib.h"
#include  "system/collisionFunctions.h"
#include "system/draw.h"

Vector2 middleScreen = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
extern Font customFont;

Vector2 Screen = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
Button playButton = createButton("     PLAY", DARKGREEN);
Button howToPlayButton = createButton("   RULES", YELLOW);
Button optionsButton = createButton("  OPTIONS ", YELLOW);
Button creditsButton = createButton("  CREDITS ", YELLOW);
Button exitButton = createButton("   EXIT", RED);

Texture2D titleTexture ;
bool firstTime = true;
void statesMenu(GameStates& gamestate)
{
    if(firstTime)
    {
        titleTexture = LoadTexture("res/montain_bakground.png");
        firstTime = false;
    }
    middleScreen = {static_cast<float>(GetScreenWidth()) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f};
    playButton = createButton(middleScreen.x - playButton.rec.width / 2, middleScreen.y - playButton.rec.height / 2,
                              "   PLAY", DARKGREEN);
    howToPlayButton = createButton(middleScreen.x - howToPlayButton.rec.width / 2,
                                   playButton.rec.y + howToPlayButton.rec.height * 2, howToPlayButton.buttonTittle,
                                   howToPlayButton.color);
    optionsButton = createButton(middleScreen.x - optionsButton.rec.width / 2,
                                 howToPlayButton.rec.y + optionsButton.rec.height * 2, optionsButton.buttonTittle,
                                 optionsButton.color);
    creditsButton = createButton(middleScreen.x - creditsButton.rec.width / 2,
                                 optionsButton.rec.y + creditsButton.rec.height * 2, creditsButton.buttonTittle,
                                 creditsButton.color);
    exitButton = createButton(middleScreen.x - exitButton.rec.width / 2,
                              creditsButton.rec.y + exitButton.rec.height * 2, exitButton.buttonTittle,
                              exitButton.color);
    Vector2 mousePoint = GetMousePosition();
    
    if (isPointRecColliding(mousePoint, playButton.rec))
    {
        playButton.isOverThisButton = true;


        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            gamestate = GameStates::Game;
            //GameLogic::initGame();
        }
    }
    else
    {
        playButton.isOverThisButton = false;
    }
    if (isPointRecColliding(mousePoint, howToPlayButton.rec))
    {
        howToPlayButton.isOverThisButton = true;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            setGameState(GameStates::Rules);
        }
    }
    else
    {
        howToPlayButton.isOverThisButton = false;
    }
    if (isPointRecColliding(mousePoint, optionsButton.rec))
    {
        optionsButton.isOverThisButton = true;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            setGameState(GameStates::Options);
        }
    }
    else
    {
        optionsButton.isOverThisButton = false;
    }

    if (isPointRecColliding(mousePoint, creditsButton.rec))
    {
        creditsButton.isOverThisButton = true;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            setGameState(GameStates::Credits);
        }
    }
    else
    {
        creditsButton.isOverThisButton = false;
    }
    if (isPointRecColliding(mousePoint, exitButton.rec))
    {
        exitButton.isOverThisButton = true;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            gamestate = GameStates::Exit;
        }
    }
    else
    {
        exitButton.isOverThisButton = false;
    }
}

void drawMenu()
{
    float width = static_cast<float>(GetScreenWidth());
    float height = static_cast<float>(GetScreenHeight());
    drawTexture(titleTexture, {0, 0}, 0, 0.7f, WHITE);
    drawButton(playButton);
    drawButton(howToPlayButton);
    drawButton(optionsButton);
    drawButton(creditsButton);
    drawButton(exitButton);
    float fontSize;
    fontSize = 16.0f * static_cast<float>(GetScreenHeight()) / 728.0f;
    std::string titleScreen = "Moon Patrol";
    drawText(titleScreen.c_str(), width / 2.0f - static_cast<float>(titleScreen.length()) * fontSize * 2.f,
             (height / 8.0f), fontSize * 8.0f, BLACK, customFont);
}
