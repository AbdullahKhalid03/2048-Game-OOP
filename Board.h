#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"
#include "animation.h"
#include <map>
#include <vector>

class Board {
protected:
    int score;
    int highScore;
    bool reset;
    int gridSize;
    std::vector<std::vector<Tile*>> grid;  // Changed to 2D vector
    std::map<int, ALLEGRO_BITMAP*> tileImages;

public:
    // Constructor
    Board();
    Board(int currentLevel);
    ~Board();

    // Getter Functions
    int getGridSize() const;
    void setGridSize(int s);
    int get_score() const;
    int get_highScore() const;
    bool get_reset() const;
    Tile* getTile(int row, int col) const;
    ALLEGRO_BITMAP* getTileBitmap(int value);
    bool isGameOver() const;
    std::vector<std::vector<Tile*>>& getGrid();  // Changed return type

    // Setter Functions
    void set_reset(bool v);
    void ScoreOnBoard(int s);
    void resetScore();
    void initialize(ALLEGRO_BITMAP* tileImgs[]);
    void drawBoard(const Animation* animation = nullptr);
    void addTile(int num, int row, int col);
    void finalizeMerges();
    void moveTile(int fromRow, int fromCol, int toRow, int toCol);
    void clearTile(int row, int col);
    void generateRandomTile();
    bool isEmpty() const;
};
#endif#pragma once
