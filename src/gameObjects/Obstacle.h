#pragma once
#include "raylib.h"
class Obstacle
{
private:
	Rectangle rec;

public:
	Obstacle();
	~Obstacle();
	void changePosX();
	void draw();
	Rectangle getRec();
};