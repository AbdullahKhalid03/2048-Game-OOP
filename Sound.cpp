#include "Sound.h"
#include "manageAllegro.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Constant.h"

Sound::Sound() {
    if (!al_is_audio_installed()) {
        al_install_audio();
        al_init_acodec_addon();
        al_reserve_samples(3);
    }
    loadSounds();
}

bool Sound::loadSounds() {
    collisionSound = al_load_sample("collision.wav");
    must_init(collisionSound, "Collision Sound");
    gameOverSound = al_load_sample("game over.wav");
    must_init(gameOverSound, "Game Over");
    winSound = al_load_sample("win sound.wav");
    must_init(winSound, "win Sound");
    return true;
}

void Sound::playCollisionSound() {
    if (collisionSound)
        al_play_sample(collisionSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
}

void Sound::playGameOverSound() {
    if (gameOverSound)
        al_play_sample(gameOverSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
}

void Sound::playWinSound() {
    if (winSound)
        al_play_sample(winSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
}

Sound::~Sound() {
    if (collisionSound) al_destroy_sample(collisionSound);
    if (gameOverSound) al_destroy_sample(gameOverSound);
}