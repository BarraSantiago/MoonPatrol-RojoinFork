#include "Character.h"
#include "raylib.h"
#include "system/draw.h"

Character::Character()
{
	this->rec = { 200,400,50,50 };
}

Character::~Character()
{
}

void Character::changePos()
{
	if (IsKeyPressed(KEY_UP) && rec.y == 400)
	{
		rec.y = 600;
	}
	else if (IsKeyPressed(KEY_DOWN) && rec.y == 600)
	{
		rec.y = 400;
	}
}

void Character::drawCharacter()
{
	DrawRectangle(rec.x, rec.y, rec.width, rec.height, RED);
}
