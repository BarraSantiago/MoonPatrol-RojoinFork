#pragma once
#include "circle.h"
#include "raylib.h"

bool isCircleCircleColliding(Circle circle1, Circle circle2);

bool isPointRecColliding(Vector2 mouse, Rectangle rec);

bool isRecRecColliding(Rectangle rec, Rectangle rec2);
bool isCircleRectColliding(Circle circle, Rectangle rectangle);