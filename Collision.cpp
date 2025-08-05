#include "Collision.h"
#include "Tile.h"

bool Collision::can_merge(Tile* a, Tile* b) {
    return (a != nullptr && b != nullptr && a->get_tile_number() == b->get_tile_number() &&
        !a->has_merged() && !b->has_merged());
}

void Collision::merge_tiles(Tile* a, Tile* b, Board* board) { //Kashish: b is the tile the two objects merge in. a is the tile in question. 
    //after merging, b is the merged tile and a disappears. 
    if (can_merge(a, b)) {
        // Combine them
        int newNumber = b->get_tile_number() * 2;
        b->set_tile_number(newNumber);
        b->set_merged(true);     // Mark as merged
        delete a;
        a = nullptr;
    }

}

Tile* Collision::CheckUpTileCollision(int tile_row, int tile_column, Board* board) {
    return board->getTile(tile_row - 1, tile_column);
}

Tile* Collision::CheckDownTileCollision(int tile_row, int tile_column, Board* board) {
    return board->getTile(tile_row + 1, tile_column);
}

Tile* Collision::CheckLeftTileCollision(int tile_row, int tile_column, Board* board) {
    return board->getTile(tile_row, tile_column - 1);
}

Tile* Collision::CheckRightTileCollision(int tile_row, int tile_column, Board* board) {
    return board->getTile(tile_row, tile_column + 1);
}

void Collision::reset_merged_flags(Board* board) {
    auto& grid = board->getGrid();
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[row].size(); ++col) {
            if (grid[row][col] != nullptr) {
                grid[row][col]->set_merged(false);
            }
        }
    }
}