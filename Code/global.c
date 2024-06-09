#include "global.h"
#include "shapes/Shape.h"
#include <stdbool.h>
// variables for global usage
const double FPS = 60.0;
const int WIDTH = 900;
const int HEIGHT = 672;
int window = 0;
int tot_score = 0;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
//bool key_state[ALLEGRO_KEY_MAX];
bool key_last_state[ALLEGRO_KEY_MAX];

void init_event_queue() {
    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "Failed to create event queue!\n");
    }
    memset(key_state, false, sizeof(key_state));
    memset(key_last_state, false, sizeof(key_last_state));
}
void update_key_state(ALLEGRO_EVENT *event) {
    if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
        key_state[event->keyboard.keycode] = true;
    } else if (event->type == ALLEGRO_EVENT_KEY_UP) {
        key_state[event->keyboard.keycode] = false;
    }
}
bool is_key_pressed(int keycode) {
    return key_state[keycode] && !key_last_state[keycode];
}

void update_last_key_state() {
    memcpy(key_last_state, key_state, sizeof(key_state));
}

ALLEGRO_EVENT event;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES] = {false};
Point mouse;
bool debug_mode = true;
