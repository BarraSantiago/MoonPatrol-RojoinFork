#include <raylib.h>
#include "creditsState.h"

#include <string>

#include  "../gameStatesEnum.h"
#include "system/draw.h"
#include "../button.h"

extern Font customFont;
Texture2D creditsTexture;
extern Button escapeButton;
int TextSize(std::string text, int fontSize);

void statesCredits()
{
    Vector2 mousePoint = GetMousePosition();
    escapeButton = createButton(0, static_cast<float>(GetScreenHeight()) - escapeButton.rec.height * 2,
                                escapeButton.buttonTittle, escapeButton.color);
    if (CheckCollisionPointRec(mousePoint, escapeButton.rec))
    {
        escapeButton.isOverThisButton = true;

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            setGameState(GameStates::Menu);
        }
    }
    else
    {
        escapeButton.isOverThisButton = false;
    }
}

void drawCredits()
{
    ClearBackground(BLACK);
    static constexpr Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    static constexpr Color DIFDARKGRAY = CLITERAL(Color){245, 245, 245, 60};

    const int fontSize = (GetScreenWidth()) / 40;
    const int textX = (GetScreenWidth()) / 50;
    const int textY = (GetScreenHeight()) / 10;
    const int xPos = GetScreenWidth() / 15;
    int index = 0;

    const std::string creditsLinkedin = "Linkedin";
    const std::string creditsItchio = " Itchio";
    const std::string creditsArtStation = "ArtStation";
    const float linkedinSize = static_cast<float>(MeasureText(creditsLinkedin.c_str(), fontSize)) * 1.1f;
    const float itchioSize = static_cast<float>(MeasureText(creditsItchio.c_str(), fontSize)) * 1.1f;
    const float artstationSize = static_cast<float>(MeasureText(creditsArtStation.c_str(), fontSize)) * 1.1f;

    const std::string creditNames[] =
    {
        "Game Made By Ignacio Arrastua",
        "                   & Santiago Barra",
        "Game Sprites Made By Leandro Josüe Riquelme Quispe",
        "Game Background by Nata Shadrina",
        "                          & Saturn-9",
        "                          & Craftpix"
    };
    const std::string creditLinks[] =
    {
        "https://rojoin.itch.io/",
        "https://www.linkedin.com/in/santiago-barra-13a849236/",
        "https://santiagobarra.itch.io/",
        "https://www.artstation.com/xrayo",
        "https://www.artstation.com/octo_hat",
        "https://www.artstation.com/saturn-9",
        "https://craftpix.net/"

    };
    index = 0;
    float linkPosition[7];
    for (std::string creditText : creditNames)
    {
        linkPosition[index] = (static_cast<float>(TextSize(creditText, fontSize)) + xPos) * 0.98f;

        index++;
    }

    const Rectangle creditRectangles[] =
    {
        {linkPosition[0], static_cast<float>(textY), linkedinSize, static_cast<float>(fontSize)},
        {linkPosition[1], static_cast<float>(textY * 2), linkedinSize, static_cast<float>(fontSize)},
        {linkPosition[1] + linkedinSize, static_cast<float>(textY * 2), itchioSize, static_cast<float>(fontSize)},
        {linkPosition[2], static_cast<float>(textY * 3), artstationSize, static_cast<float>(fontSize)},
        {linkPosition[3], static_cast<float>(textY * 4), artstationSize, static_cast<float>(fontSize)},
        {linkPosition[4], static_cast<float>(textY * 5), artstationSize, static_cast<float>(fontSize)},
        {linkPosition[5], static_cast<float>(textY * 6), artstationSize, static_cast<float>(fontSize)},
    };

    index = 0;
    for (auto creditName : creditNames)
    {
        Color color;
        switch (index)
        {
        case 0:
        case 1:
            color = RED;
            break;
        case 2:
            color = NEONCYAN;
            break;
        default:
            color = GREEN;
        }
        drawText(creditName.c_str(), textX, textY + textY * index, fontSize, color);
        index++;
    }
    drawText(creditNames[1].c_str(), textX, textY * 2, fontSize, NEONCYAN);
    drawText(creditNames[2].c_str(), textX, textY * 3, fontSize, NEONCYAN);


    index = 0;

    for (Rectangle creditRectangle : creditRectangles)
    {
        index++;
        if (CheckCollisionPointRec(GetMousePosition(), creditRectangle))
        {
            DrawRectangleRec(creditRectangle, DIFDARKGRAY);
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                OpenURL(creditLinks[index > 1 ? index - 1 : index].c_str());
            }
        }
    }

    DrawText(creditsItchio.c_str(), xPos + TextSize(creditNames[0], fontSize),
             textY, fontSize, RAYWHITE);

    DrawText(creditsLinkedin.c_str(), xPos + TextSize(creditNames[1], fontSize),
             textY * 2, fontSize, RAYWHITE);

    DrawText(creditsItchio.c_str(), xPos + TextSize(creditNames[1], fontSize) + TextSize(creditsLinkedin, fontSize),
             textY * 2, fontSize, RAYWHITE);
    for (int i = 0; i < 4; ++i)
    {
        DrawText(creditsArtStation.c_str(), static_cast<int>(creditRectangles[3 + i].x * 1.02f),
                 static_cast<int>(creditRectangles[3 + i].y), fontSize, RAYWHITE);
    }
    drawButton(escapeButton);
}

int TextSize(std::string text, int fontSize)
{
    return MeasureText(text.c_str(), fontSize);
}
