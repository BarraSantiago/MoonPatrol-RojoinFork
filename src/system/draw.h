#pragma once
#include "raylib.h"

void drawTexture(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);
void drawTexture(Texture2D texture, Rectangle source, Rectangle dest, Vector2 position, float rotation, float scale,
                 Color tint);
void drawText(const char* text, int posX, int posY, int fontSize, Color color);
void drawText(const char* text, float posX, float posY, float fontSize, Color color, Font font);
int getScaleWidth();
int getScaleHeight();
void updateScale();
