#include "collisionFunctions.h"

#include <iostream>

#include  "cmath"

bool isCircleCircleColliding(Circle circle1, Circle circle2)
{
	
	float distanceY = circle1.position.y -circle2.position.y;
	float distanceX = circle1.position.x -circle2.position.x;
	float distance = sqrt((distanceX* distanceX) + (distanceY*distanceY));

 	if (distance < circle1.radius + circle2.radius)
	{
		return true;
	}
	return false;
	
}

bool isPointRecColliding(Vector2 mouse, Rectangle rec) //Check if works
{
	float rightEdge = rec.x + rec.width ;
	float leftEdge = rec.x;
	float upEdge = rec.y;
	float downEdge = rec.y + rec.height;

	if (mouse.x <= rightEdge && mouse.x >= leftEdge && mouse.y >= upEdge && mouse.y <= downEdge)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isRecRecColliding(Rectangle rec, Rectangle rec2)
{

	float rec1RightEdge = rec.x + rec.width;
	float rec1LeftEdge = rec.x;
	float rec1UpEdge = rec.y;
	float rec1DownEdge = rec.y + rec.height;
	
	float rec2RightEdge = rec2.x + rec2.width;
	float rec2LeftEdge = rec2.x;
	float rec2UpEdge = rec2.y;
	float rec2DownEdge = rec2.y + rec2.height;

	if (rec1RightEdge >= rec2LeftEdge &&     // r1 right edge past r2 left
		rec1LeftEdge <= rec2RightEdge &&       // r1 left edge past r2 right
		rec1DownEdge >= rec2UpEdge &&       // r1 top edge past r2 bottom
		rec1UpEdge <= rec2DownEdge) {       // r1 bottom edge past r2 top
		return true;
	}
	return false;
}
