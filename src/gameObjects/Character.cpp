#include "Character.h"
#include "raylib.h"
#include "system/draw.h"

Character::Character()
{
	rec = { 200.0f,600.0f,50,50 };
	playerDead = false;
	gravity = 9.86f;
}

Character::~Character()
{
}

void Character::changePos()
{
	if (IsKeyPressed(KEY_DOWN) && rec.y == 400.0f)
	{
		rec.y = 600.0f;
	}
	else if (IsKeyPressed(KEY_UP) && rec.y == 600.0f)
	{
		rec.y = 400.0f;
	}
}

void Character::draw()
{
	DrawRectangle((int)rec.x, (int)rec.y, (int)rec.width, (int)rec.height, RED);
}

void Character::update()
{
	if (rec.y <= 600.0f)
	{
		rec.y += gravity * GetFrameTime()*1.0f;
	}
	else if (rec.y > 600.0f)
	{
		rec.y = 600.0f;
	}
}

void Character::jump()
{
	jumpState = true;

}

Rectangle Character::getRec()
{
	return rec;
}

bool Character::isPlayerDead()
{
	return playerDead;
}

void Character::setPlayerDeadStatus(bool status)
{
	playerDead = status;
}
