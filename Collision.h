#pragma once
#ifndef COLLISION_H
#define COLLISION_H
#include "Tile.h"
#include  "Board.h"

class Collision : virtual public Board {
public:
	bool can_merge(Tile* a, Tile* b);
	void merge_tiles(Tile* a, Tile* b, Board* board);
	Tile* CheckUpTileCollision(int tile_row, int tile_column, Board* board);
	Tile* CheckDownTileCollision(int tile_row, int tile_column, Board* board);
	Tile* CheckLeftTileCollision(int tile_row, int tile_column, Board* board);
	Tile* CheckRightTileCollision(int tile_row, int tile_column, Board* board);
	void reset_merged_flags(Board* board);
};

#endif
#pragma once
