#include "Obstacle.h"
#include "raylib.h"

Obstacle::Obstacle()
{
	rec = { 1280,600,75 ,150 };
}
Obstacle::~Obstacle()
{

}

void Obstacle::reset()
{
	rec = { 1280,600,75 ,150 };
}

void Obstacle::changePosX()
{
	rec.x -= 200 * GetFrameTime();
	if (rec.x<0)
	{
		rec.x = (float)GetScreenWidth();
	}
}

void Obstacle::draw()
{
	DrawRectangle((int)rec.x, (int)rec.y, (int)rec.width, (int)rec.height, BLUE);
}

Rectangle Obstacle::getRec()
{
	return rec;
}

