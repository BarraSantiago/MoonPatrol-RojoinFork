#pragma once
#include "raylib.h"
#include "system/circle.h"

class Character
{
private:
    Circle body{};
    bool alive;
    bool jumpState;
    float gravity;
    int hp;
public:
    Character();
    ~Character();
    void reset();
    void changePos();
    void draw();
    void update();
    void jump();
    Circle GetBody() const;
    bool isAlive() const;
    void SetHitPoints(int hpModifier);
};
