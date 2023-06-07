#include "global.h"

// variables for global usage
const double FPS = 60.0;
const int WIDTH = 900;
const int HEIGHT = 500;
int window = 0;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool debug_mode = true;
