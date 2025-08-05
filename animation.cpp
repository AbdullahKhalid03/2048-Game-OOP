#include "animation.h"
#include "Board.h"
#include "Constant.h"
#include <allegro5/allegro5.h>

void Animation::addMovingTile(Tile* tile, int startRow, int startCol, int endRow, int endCol, int value,
    bool willMerge, Tile* mergeTarget) {
    // If already animating this tile, update its destination
    for (auto& anim : animatingTiles) {
        if (anim.tile == tile) {
            anim.endRow = endRow;
            anim.endCol = endCol;
            anim.merging = willMerge;
            anim.mergeDest = mergeTarget;
            return;
        }
    }

    // Otherwise add a new animating tile
    animatingTiles.emplace_back(tile, startRow, startCol, endRow, endCol, value, willMerge, mergeTarget);
    animationActive = true;
}

void Animation::clear() {
    animatingTiles.clear();
    animationActive = false;
}

bool Animation::update() {
    if (!animationActive) return false;

    bool stillAnimating = false;

    for (auto& anim : animatingTiles) {
        // Update progress
        anim.progress += animationSpeed;

        // Cap at 1.0
        if (anim.progress > 1.0f) {
            anim.progress = 1.0f;
        }

        // Check if any animations are still running
        if (anim.progress < 1.0f) {
            stillAnimating = true;
        }
    }

    // If all animations complete, clear them
    if (!stillAnimating) {
        animationActive = false;
    }

    return stillAnimating;
}

void Animation::drawAnimatingTiles(Board* board, int offsetX, int offsetY) {
    for (const auto& anim : animatingTiles) {
        // Calculate current position
        float currentX = anim.startCol * TILE_WIDTH + (anim.endCol - anim.startCol) * TILE_WIDTH * anim.progress;
        float currentY = anim.startRow * TILE_HEIGHT + (anim.endRow - anim.startRow) * TILE_HEIGHT * anim.progress + 100;

        // Get the bitmap based on the tile's value
        ALLEGRO_BITMAP* bitmap = board->getTileBitmap(anim.value);

        // Draw the tile at the interpolated position
        if (bitmap != nullptr) {
            al_draw_bitmap(bitmap, currentX + offsetX, currentY + offsetY, 0);
        }
    }
}