
#include <allegro5/allegro_audio.h>

class Sound {
private:
    ALLEGRO_SAMPLE* collisionSound = nullptr;
    ALLEGRO_SAMPLE* gameOverSound = nullptr;
    ALLEGRO_SAMPLE* winSound = nullptr;

public:
    Sound();
    ~Sound();

    void playCollisionSound();
    void playGameOverSound();
    void playWinSound();

    bool loadSounds();  // Separate loading function
};
#pragma once
