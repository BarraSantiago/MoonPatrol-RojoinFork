#pragma once
#include "raylib.h"

class Character
{
private:
	Rectangle rec;
public:
	Character();
	~Character();
	void changePos();
	void drawCharacter();
};

