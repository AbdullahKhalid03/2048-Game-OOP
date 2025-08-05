#include "run.h"

Run::Run() : allegro(SCREENWIDTH, SCREENHEIGHT), inputEnabled(true), currentLevel(0) {
    display = allegro.get_display();
    timer = allegro.get_timer();
    event_queue = allegro.get_event_queue();
    std::srand(std::time(0));

    board = Board(2);

    for (int i = 0; i < 11; i++) {
        tileImgs[i] = nullptr;
    }
    for (int i = 0; i < 3; i++) {
        board_imgs[i] = nullptr;
    }
}


void Run::registerEvents() {
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

void Run::handleInput(ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_KEY_DOWN && inputEnabled) {
        bool moved = false;

        if (!animation.isActive()) {
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                moved = direction.moveUp(&board, &collide, &animation);
                if (moved) { sound.playCollisionSound(); } break;
            case ALLEGRO_KEY_DOWN:
                moved = direction.moveDown(&board, &collide, &animation);
                if (moved) { sound.playCollisionSound(); }
                break;
            case ALLEGRO_KEY_LEFT:
                moved = direction.moveLeft(&board, &collide, &animation);
                if (moved) { sound.playCollisionSound(); } break;
            case ALLEGRO_KEY_RIGHT:
                moved = direction.moveRight(&board, &collide, &animation);
                if (moved) { sound.playCollisionSound(); } break;
            }

            if (moved && animation.isActive()) {
                inputEnabled = false;
            }
        }
    }
}

void Run::loadAssets() {
    board_imgs[0] = al_load_bitmap("board_2.png"); // 2x2 board
    board_imgs[1] = al_load_bitmap("board_3.png"); // 3x3 board
    board_imgs[2] = al_load_bitmap("board.png"); // 4x4 board

    for (int i = 0; i < 3; i++) {
        must_init(board_imgs[i], "board image");
    }

    tileImgs[0] = al_load_bitmap("2_tile.png");
    tileImgs[1] = al_load_bitmap("4_tile.png");
    tileImgs[2] = al_load_bitmap("8_tile.png");
    tileImgs[3] = al_load_bitmap("16_tile.png");
    tileImgs[4] = al_load_bitmap("32_tile.png");
    tileImgs[5] = al_load_bitmap("64_tile.png");
    tileImgs[6] = al_load_bitmap("128_tile.png");
    tileImgs[7] = al_load_bitmap("256_tile.png");
    tileImgs[8] = al_load_bitmap("512_tile.png");
    tileImgs[9] = al_load_bitmap("1024_tile.png");
    tileImgs[10] = al_load_bitmap("2048_tile.png");

    for (int i = 0; i < 11; ++i) {
        must_init(tileImgs[i], "tile image");
    }

    board.initialize(tileImgs);
    board.generateRandomTile();
    board.generateRandomTile();
}

void Run::update() {
    if (animation.isActive()) {
        bool stillAnimating = animation.update();

        if (!stillAnimating) {
            board.finalizeMerges();
            inputEnabled = true;

            if (checkWinCondition()) {
                advanceLevel();
            }
            else if (board.isEmpty()) {
                board.generateRandomTile();
            }
            else if (board.isGameOver()) {
                sound.playGameOverSound();
                cout << "Game Over!" << endl;
                board.set_reset(true);
            }
        }
    }
}

bool Run::checkWinCondition() {
    for (int r = 0; r < board.getGridSize(); ++r) {
        for (int c = 0; c < board.getGridSize(); ++c) {
            Tile* tile = board.getTile(r, c);
            if (tile && tile->get_tile_number() >= winConditions[currentLevel]) {
                sound.playWinSound();
                return true;
            }
        }
    }
    return false;
}

void Run::advanceLevel() {
    currentLevel++;
    if (currentLevel > 2) {
        cout << "Congratulations! You've completed all levels!" << endl;
        currentLevel = 0; // Reset to first level
    }

    int newSize = currentLevel + 2;
    board = Board(newSize);
    board.initialize(tileImgs);
    board.generateRandomTile();
    board.generateRandomTile();

    cout << "Advanced to level " << (currentLevel + 1) << "!" << endl;
    sound.playWinSound();
}

void Run::runGame() {
    loadAssets();
    registerEvents();

    al_start_timer(timer);
    bool running = true;
    bool redraw = true;

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                running = false;
            else
                handleInput(event);
        }
        else if (event.type == ALLEGRO_EVENT_TIMER) {
            update();
            redraw = true;
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(187, 173, 160));
            // Draw the appropriate board image for current level
            al_draw_bitmap(board_imgs[currentLevel], 0, 100, 0);

            al_draw_textf(allegro.get_font(), al_map_rgb(76, 100, 40), 10, 30, 0,
                "Score: %d", board.get_score());
            al_draw_textf(allegro.get_font(), al_map_rgb(76, 100, 64), 10, 50, 0,
                "High Score: %d", board.get_highScore());
            al_draw_textf(allegro.get_font(), al_map_rgb(76, 100, 64), 10, 70, 0,
                "Level: %d/3 (Target: %d)", currentLevel + 1, winConditions[currentLevel]);

            board.drawBoard(&animation);

            if (animation.isActive()) {
                animation.drawAnimatingTiles(&board, offset_X, offset_Y);
            }

            al_flip_display();
        }
    }
}