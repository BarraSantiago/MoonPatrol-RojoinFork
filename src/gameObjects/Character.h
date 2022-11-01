#pragma once
#include "raylib.h"

class Character
{
private:
	Rectangle rec;
	bool isPlayerDead;
public:
	Character();
	~Character();
	void changePos();
	void drawCharacter();
	Rectangle getRec();
};

