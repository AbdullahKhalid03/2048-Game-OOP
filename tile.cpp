#include <iostream>
#include "Tile.h"

//Constructor
Tile::Tile(int num, int r, int c, ALLEGRO_BITMAP* img)
	: number(num), row(r), col(c), tileImg(img), mergedThisTurn(false), shouldMerge(false) {
}

//Destructor
Tile::~Tile() {}

//Setter functions
void Tile::set_tile_col(int j) { col = j; }
void Tile::set_tile_row(int i) { row = i; }
void Tile::set_tile_number(int n) { if (n > 0 && n % 2 == 0 && n % 3 != 0) { number = n; } else { std::cout << "Invalid Number " << n << std::endl; } }
void Tile::set_merged(bool m) { mergedThisTurn = m; }
void Tile::set_tile_image(ALLEGRO_BITMAP* img) { tileImg = img; }
void Tile::set_position(int new_row, int new_col) { row = new_row; col = new_col; }
void Tile::set_should_merge(bool s) { shouldMerge = s; }

//Getter Functions
int Tile::get_tile_row()const { return row; }
int Tile::get_tile_col()const { return col; }
int Tile::get_tile_number()const { return number; }
bool Tile::has_merged() const { return mergedThisTurn; }
ALLEGRO_BITMAP* Tile::get_tile_image()const { return tileImg; }
bool Tile::get_should_merge() const { return shouldMerge; }
