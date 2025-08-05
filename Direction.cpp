#include "Direction.h"
#include "animation.h"
#include <iostream>

bool Direction::moveUp(Board* board, Collision* collision, Animation* animation) {
    bool moved = false;
    auto& grid = board->getGrid();

    // Clear any existing animations if we're starting a new move
    if (!animation->isActive()) {
        animation->clear();
    }

    // Reset merged flags for all tiles
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            if (grid[row][col] != nullptr) {
                grid[row][col]->set_merged(false);
            }
        }
    }

    // Move tiles up, starting from second row (row 1)
    for (int row = 1; row < grid.size(); row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            Tile* currentTile = board->getTile(row, col);

            if (currentTile != nullptr) {
                int currentRow = row;
                int targetRow = row;
                bool willMerge = false;
                Tile* mergeTarget = nullptr;

                // Find where this tile will end up
                while (targetRow > 0) {
                    Tile* aboveTile = collision->CheckUpTileCollision(targetRow, col, board);

                    if (aboveTile == nullptr) {
                        // Empty space above, can move up
                        targetRow--;
                    }
                    else if (collision->can_merge(currentTile, aboveTile)) {
                        // Can merge with the tile above
                        targetRow--;
                        willMerge = true;
                        mergeTarget = aboveTile;
                        break;
                    }
                    else {
                        // Can't move further
                        break;
                    }
                }

                // If the tile will move, add it to animation
                if (targetRow != currentRow) {
                    moved = true;
                    animation->addMovingTile(
                        currentTile,
                        currentRow, col,
                        targetRow, col,
                        currentTile->get_tile_number(),
                        willMerge,
                        mergeTarget
                    );

                    // The actual board update will happen after animation completes
                    if (!willMerge) {
                        // Just moving
                        board->moveTile(currentRow, col, targetRow, col);
                    }
                    else {
                        mergeTarget->set_should_merge(true);
                        mergeTarget->set_merged(true);
                        board->clearTile(currentRow, col);
                    }
                }
            }
        }
    }

    return moved;
}

bool Direction::moveDown(Board* board, Collision* collision, Animation* animation) {
    bool moved = false;
    auto& grid = board->getGrid();

    // Clear any existing animations if we're starting a new move
    if (!animation->isActive()) {
        animation->clear();
    }

    // Reset merged flags for all tiles
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            if (grid[row][col] != nullptr) {
                grid[row][col]->set_merged(false);
            }
        }
    }

    // Move tiles down, starting from second-to-last row
    for (int row = grid.size() - 2; row >= 0; row--) {
        for (int col = 0; col < grid[row].size(); col++) {
            Tile* currentTile = board->getTile(row, col);

            if (currentTile != nullptr) {
                int currentRow = row;
                int targetRow = row;
                bool willMerge = false;
                Tile* mergeTarget = nullptr;

                // Find where this tile will end up
                while (targetRow < grid.size() - 1) {
                    Tile* belowTile = collision->CheckDownTileCollision(targetRow, col, board);

                    if (belowTile == nullptr) {
                        // Empty space below, can move down
                        targetRow++;
                    }
                    else if (collision->can_merge(currentTile, belowTile)) {
                        // Can merge with the tile below
                        targetRow++;
                        willMerge = true;
                        mergeTarget = belowTile;
                        break;
                    }
                    else {
                        // Can't move further
                        break;
                    }
                }

                // If the tile will move, add it to animation
                if (targetRow != currentRow) {
                    moved = true;
                    animation->addMovingTile(
                        currentTile,
                        currentRow, col,
                        targetRow, col,
                        currentTile->get_tile_number(),
                        willMerge,
                        mergeTarget
                    );

                    // The actual board update will happen after animation completes
                    if (!willMerge) {
                        // Just moving
                        board->moveTile(currentRow, col, targetRow, col);
                    }
                    else {
                        mergeTarget->set_should_merge(true);
                        mergeTarget->set_merged(true);
                        board->clearTile(currentRow, col);
                    }
                }
            }
        }
    }

    return moved;
}

bool Direction::moveLeft(Board* board, Collision* collision, Animation* animation) {
    bool moved = false;
    auto& grid = board->getGrid();

    // Clear any existing animations if we're starting a new move
    if (!animation->isActive()) {
        animation->clear();
    }

    // Reset merged flags for all tiles
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            if (grid[row][col] != nullptr) {
                grid[row][col]->set_merged(false);
            }
        }
    }

    // Move tiles left, starting from second column (col 1)
    for (int col = 1; col < grid[0].size(); col++) {
        for (int row = 0; row < grid.size(); row++) {
            Tile* currentTile = board->getTile(row, col);

            if (currentTile != nullptr) {
                int currentCol = col;
                int targetCol = col;
                bool willMerge = false;
                Tile* mergeTarget = nullptr;

                // Find where this tile will end up
                while (targetCol > 0) {
                    Tile* leftTile = collision->CheckLeftTileCollision(row, targetCol, board);

                    if (leftTile == nullptr) {
                        // Empty space to the left, can move left
                        targetCol--;
                    }
                    else if (collision->can_merge(currentTile, leftTile)) {
                        // Can merge with the tile to the left
                        targetCol--;
                        willMerge = true;
                        mergeTarget = leftTile;
                        break;
                    }
                    else {
                        // Can't move further
                        break;
                    }
                }

                // If the tile will move, add it to animation
                if (targetCol != currentCol) {
                    moved = true;
                    animation->addMovingTile(
                        currentTile,
                        row, currentCol,
                        row, targetCol,
                        currentTile->get_tile_number(),
                        willMerge,
                        mergeTarget
                    );

                    // The actual board update will happen after animation completes
                    if (!willMerge) {
                        // Just moving
                        board->moveTile(row, currentCol, row, targetCol);
                    }
                    else {
                        mergeTarget->set_should_merge(true);
                        mergeTarget->set_merged(true);
                        board->clearTile(row, currentCol);
                    }
                }
            }
        }
    }

    return moved;
}

bool Direction::moveRight(Board* board, Collision* collision, Animation* animation) {
    bool moved = false;
    auto& grid = board->getGrid();

    // Clear any existing animations if we're starting a new move
    if (!animation->isActive()) {
        animation->clear();
    }

    // Reset merged flags for all tiles
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[row].size(); col++) {
            if (grid[row][col] != nullptr) {
                grid[row][col]->set_merged(false);
            }
        }
    }

    // Move tiles right, starting from second-to-last column
    for (int col = grid[0].size() - 2; col >= 0; col--) {
        for (int row = 0; row < grid.size(); row++) {
            Tile* currentTile = board->getTile(row, col);

            if (currentTile != nullptr) {
                int currentCol = col;
                int targetCol = col;
                bool willMerge = false;
                Tile* mergeTarget = nullptr;

                // Find where this tile will end up
                while (targetCol < grid[0].size() - 1) {
                    Tile* rightTile = collision->CheckRightTileCollision(row, targetCol, board);

                    if (rightTile == nullptr) {
                        // Empty space to the right, can move right
                        targetCol++;
                    }
                    else if (collision->can_merge(currentTile, rightTile)) {
                        // Can merge with the tile to the right
                        targetCol++;
                        willMerge = true;
                        mergeTarget = rightTile;
                        break;
                    }
                    else {
                        // Can't move further
                        break;
                    }
                }

                // If the tile will move, add it to animation
                if (targetCol != currentCol) {
                    moved = true;
                    animation->addMovingTile(
                        currentTile,
                        row, currentCol,
                        row, targetCol,
                        currentTile->get_tile_number(),
                        willMerge,
                        mergeTarget
                    );

                    // The actual board update will happen after animation completes
                    if (!willMerge) {
                        // Just moving
                        board->moveTile(row, currentCol, row, targetCol);
                    }
                    else {
                        mergeTarget->set_should_merge(true);
                        mergeTarget->set_merged(true);
                        board->clearTile(row, currentCol);
                    }
                }
            }
        }
    }

    return moved;
}