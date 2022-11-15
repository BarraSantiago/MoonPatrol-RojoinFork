#pragma once
#include "raylib.h"

class Character
{
private:
	Rectangle rec;
	bool playerDead;
	bool jumpState;
	float gravity;
public:
	Character();
	~Character();
	void reset();
	void changePos();
	void draw();
	void update();
	void jump();
	Rectangle getRec();
	bool isPlayerDead();
	void setPlayerDeadStatus(bool status);
};

