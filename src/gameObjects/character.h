#pragma once
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
    void draw() const;
    void update();
    void jump();
    Circle getBody() const;
    bool isAlive() const;
    void setHP(int hpModifier);
};
