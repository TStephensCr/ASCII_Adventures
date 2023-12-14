#pragma once
#include "Position.hpp"

struct Player
{
    int hp = 100;
    int shield = 20;
    int Money = 0;
    int colpi = 10;
    int points = 0;
    int bulletRange = 10;
    char LastMovement = 'd';
    bool inJump = false;
    Position previusPosition;
};
