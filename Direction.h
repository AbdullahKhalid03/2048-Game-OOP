#pragma once
#ifndef DIRECTION_H
#define DIRECTION_H

#include "Collision.h"
#include "Board.h"
#include "Tile.h"
#include "animation.h"

class Direction {
public:
    bool moveUp(Board* board, Collision* collision, Animation* animation);
    bool moveDown(Board* board, Collision* collision, Animation* animation);
    bool moveRight(Board* board, Collision* collision, Animation* animation);
    bool moveLeft(Board* board, Collision* collision, Animation* animation);
};

#endif
#pragma once
