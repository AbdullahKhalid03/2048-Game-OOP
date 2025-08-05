#pragma once
#ifndef RUN_H
#define RUN_H

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Allegro headers
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "Constant.h"
#include "manageAllegro.h"
#include "Direction.h"
#include "Tile.h"
#include "Board.h"
#include "Collision.h"
#include "animation.h"
#include "Sound.h"

class Run {
private:
    Board board;
    Direction direction;
    Collision collide;
    Animation animation;
    manageAllegro allegro;
    Sound sound;

    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* event_queue;

    ALLEGRO_BITMAP* tileImgs[11];
    ALLEGRO_BITMAP* board_imgs[3]; // For different board sizes (2x2, 3x3, 4x4)
    //ALLEGRO_BITMAP* background;

    bool inputEnabled;
    int currentLevel;
    int winConditions[3] = { 16, 128, 2048 }; // Win conditions for each level

public:
    Run();
    void loadAssets();
    void registerEvents();
    void handleInput(ALLEGRO_EVENT event);
    void update();
    void runGame();
    void advanceLevel();
    bool checkWinCondition();
};
#endif
#pragma once
