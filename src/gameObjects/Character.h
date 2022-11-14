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
	void draw();
	void update();
	Rectangle getRec();
	bool isPlayerDead();
	void setPlayerDeadStatus(bool status);
};

