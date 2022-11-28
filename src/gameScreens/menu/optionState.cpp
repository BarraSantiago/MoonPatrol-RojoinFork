#include <raylib.h>
#include "../button.h"
#include "../gameStatesEnum.h"
#include "optionsState.h"

Button backButton = createButton(" GO BACK", RED);
Button changeScreen;
Button secondPlayer;
bool secondPlayerActive = false;
static int resolutionIndex = 2;
static int maxResolutionIndex = 4;
float backgroundScale = 0.833f;

void statesOptions()
{
    backButton = createButton(0, static_cast<float>(GetScreenHeight()) - backButton.rec.height * 2,
                              backButton.buttonTittle, backButton.color);
    /*
        changeScreen = createButton(static_cast<float>(GetScreenWidth() / 4), static_cast<float>(GetScreenHeight() / 2),
                                    200, 60.0f * static_cast<float>(GetScreenHeight() / 768), "Change Res", WHITE);
        */
    secondPlayer = createButton(static_cast<float>(GetScreenWidth() / 4) * 2, static_cast<float>(GetScreenHeight() / 2),
                                200, 60.0f * static_cast<float>(GetScreenHeight() / 768), "Second player",
                                !secondPlayerActive ? WHITE : GREEN);

    Vector2 mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, backButton.rec))
    {
        backButton.isOverThisButton = true;

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            setGameState(GameStates::Menu);
        }
    }
    else
    {
        backButton.isOverThisButton = false;
    }

    if (GetScreenWidth() < 2560)
    {
        maxResolutionIndex = 3;
    }
    else if (GetScreenWidth() < 1920)
    {
        maxResolutionIndex = 2;
    }
    else if (GetScreenWidth() < 1600)
    {
        maxResolutionIndex = 1;
    }

    if (CheckCollisionPointRec(mousePoint, changeScreen.rec))
    {
        changeScreen.isOverThisButton = true;

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            resolutionIndex++;
            if (resolutionIndex > maxResolutionIndex)
            {
                resolutionIndex = 1;
            }
        }
    }
    else
    {
        changeScreen.isOverThisButton = false;
    }

    if (CheckCollisionPointRec(mousePoint, secondPlayer.rec))
    {
        secondPlayer.isOverThisButton = true;

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            secondPlayerActive = !secondPlayerActive;
        }
    }
    else
    {
        secondPlayer.isOverThisButton = false;
    }

    switch (resolutionIndex)
    {
    case 1:
        SetWindowSize(1024, 768);
        backgroundScale = .76f;
        break;
    case 2:
        SetWindowSize(1600, 900);
        backgroundScale = .833f;
        break;
    case 3:
        SetWindowSize(1920, 1080);
        backgroundScale = 1.f;
        break;
    case 4:
        SetWindowSize(2560, 1440);
        backgroundScale = 1.33f;
        break;
    }
}

void drawOptions()
{
    ClearBackground(BLACK);
    drawButton(changeScreen);
    drawButton(secondPlayer);
    drawButton(backButton);
}
