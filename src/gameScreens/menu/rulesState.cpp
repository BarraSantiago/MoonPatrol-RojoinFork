#include <raylib.h>
#include  "rulesState.h"
#include  "../gameStatesEnum.h"
#include "system/draw.h"
#include "../button.h"

extern Font customFont;
Button escapeButton = createButton(" GO BACK", RED);
Texture2D rulesTexture;
static bool firstTime = true;

void statesRules()
{
    if (firstTime)
    {
        rulesTexture = LoadTexture("res/rules.png");
        firstTime = false;
    }
    Vector2 mousePoint = GetMousePosition();
    escapeButton = createButton(0, static_cast<float>(GetScreenHeight()) - escapeButton.rec.height * 2,
                                escapeButton.buttonTittle, escapeButton.color);
    if (CheckCollisionPointRec(mousePoint, escapeButton.rec))
    {
        escapeButton.isOverThisButton = true;

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            setGameState(GameStates::Menu);
            UnloadTexture(rulesTexture);
            firstTime = true;
        }
    }
    else
    {
        escapeButton.isOverThisButton = false;
    }
}

void drawRules()
{
    extern float backgroundScale;

    ClearBackground(BLACK);

    drawTexture(rulesTexture, {0, 0}, 0, backgroundScale, WHITE);
    drawButton(escapeButton);
}
