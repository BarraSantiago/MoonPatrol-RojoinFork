#include "Obstacle.h"
#include "raylib.h"

Obstacle::Obstacle()
{
	rec = { 1280,600,75 ,150 };
}
Obstacle::~Obstacle()
{

}
void Obstacle::changePosX()
{
	rec.x -= 200 * GetFrameTime();
	if (rec.x<0)
	{
		rec.x = GetScreenWidth();
	}
}
