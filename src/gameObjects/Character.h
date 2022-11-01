#pragma once
#include "raylib.h"

class Character
{
private:
	Rectangle rec;
	bool playerDead;
public:
	Character();
	~Character();
	void changePos();
	void drawCharacter();
	Rectangle getRec();
	bool isPlayerDead();
};

