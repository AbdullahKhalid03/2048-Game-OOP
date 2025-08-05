#pragma once
#pragma once
#ifndef TILE_H
#define TILE_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Tile {
private:
	int number; //The number on the tile
	int row;	//The row of the tile on the board
	int col;	//The col of the tile on the board
	ALLEGRO_BITMAP* tileImg;	//The bitmap(image) of the tile
	bool mergedThisTurn;		//Checks if the tiles has merged or not
	bool shouldMerge;			//Checks if the tile should merge in the next step

public:
	//constructor
	Tile(int num, int r, int c, ALLEGRO_BITMAP* img);

	//destructor. virtual because other classes inherit Tile class
	virtual ~Tile();

	//getter functions
	int get_tile_number()const;
	int get_tile_row()const;
	int get_tile_col()const;
	ALLEGRO_BITMAP* get_tile_image()const;
	bool has_merged() const;
	bool get_should_merge() const;

	//setter functions
	void set_tile_number(int n);
	void set_tile_row(int i);
	void set_tile_col(int j);
	void set_tile_image(ALLEGRO_BITMAP* img);
	void set_should_merge(bool s);
	void set_merged(bool m);
	void set_position(int new_row, int new_col);
};

#endif

