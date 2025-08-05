#ifndef MANAGE_ALLEGRO_H
#define MANAGE_ALLEGRO_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>

class manageAllegro {
private:
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_FONT* font;
public:
    manageAllegro(int screenwidth, int screenheight);
    ~manageAllegro();
    ALLEGRO_DISPLAY* get_display() const;
    ALLEGRO_TIMER* get_timer()const;
    ALLEGRO_EVENT_QUEUE* get_event_queue() const;
    ALLEGRO_FONT* get_font() const;
};
#endif#pragma once
#pragma once
