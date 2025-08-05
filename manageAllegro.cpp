#include "manageAllegro.h"
#include "Constant.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

manageAllegro::manageAllegro(int screenWidth, int screenHeight)
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    timer = al_create_timer(1.0 / 40.0);
    must_init(timer, "timer");

    queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    disp = al_create_display(screenWidth, screenHeight);
    must_init(disp, "display");

    font = al_create_builtin_font();
    must_init(font, "font");

    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_init_image_addon(), "image addon");
}

manageAllegro::~manageAllegro() {
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}

ALLEGRO_DISPLAY* manageAllegro::get_display() const {
    return disp;
}
ALLEGRO_TIMER* manageAllegro::get_timer() const {
    return timer;
}
ALLEGRO_EVENT_QUEUE* manageAllegro::get_event_queue() const {
    return queue;
}
ALLEGRO_FONT* manageAllegro::get_font() const {
    return font;
}