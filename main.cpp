#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Run.h"
using namespace std;

// .h files
#include "Constant.h"
int SCREENWIDTH = 280;
int SCREENHEIGHT = 380;
int TILE_WIDTH = 70;
int TILE_HEIGHT = 70;
int FPS = 60;
int offset_X = 5;
int offset_Y = 5;

void must_init(bool test, const char* description)
{
	if (test) return;
	else std::cout << "couldn't initialize " << description << std::endl;
	exit(1);
}


int main() {
	Run game;
	game.runGame();
	return 0;
}