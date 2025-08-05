#ifndef ANIMATION_H
#define ANIMATION_H

#include "Tile.h"
#include <vector>
#include <allegro5/allegro5.h>

class Board;  // Forward declaration

// Structure to hold data for a tile being animated
struct AnimatingTile {
    Tile* tile;           // The tile being animated
    int startRow, startCol;  // Starting position
    int endRow, endCol;      // Ending position
    int value;              // Value of the tile
    float progress;         // Animation progress (0.0 to 1.0)
    bool merging;           // Whether this tile will merge at the end
    Tile* mergeDest;        // Tile that this tile will merge with (if merging)

    AnimatingTile(Tile* t, int sRow, int sCol, int eRow, int eCol, int val, bool willMerge, Tile* mDest)
        : tile(t), startRow(sRow), startCol(sCol), endRow(eRow), endCol(eCol),
        value(val), progress(0.0f), merging(willMerge), mergeDest(mDest) {
    }
};

class Animation {
private:
    std::vector<AnimatingTile> animatingTiles;
    bool animationActive;
    float animationSpeed;  // Speed of animation (how much progress increases per frame)

public:
    Animation() : animationActive(false), animationSpeed(0.1f) {}

    // Add a tile to be animated
    void addMovingTile(Tile* tile, int startRow, int startCol, int endRow, int endCol, int value,
        bool willMerge = false, Tile* mergeTarget = nullptr);

    // Update animation progress, returns true if animation is still active
    bool update();

    // Draw all animating tiles
    void drawAnimatingTiles(Board* board, int offsetX, int offsetY);

    // Clear all animations
    void clear();

    // Check if animation is active
    bool isActive() const { return animationActive; }

    // Get all animating tiles (for board updates after animation ends)
    const std::vector<AnimatingTile>& getAnimatingTiles() const { return animatingTiles; }
};

#endif // ANIMATION_H#pragma once
