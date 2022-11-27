#pragma once
#include "gameObjects/Character.h"
#include"gameObjects/Obstacle.h"

bool isCharacterObstacleColliding(Character* character, Obstacle* obstacle);

bool isObstacleBulletColliding(Obstacle* obstacle, Bullet* bullet);
