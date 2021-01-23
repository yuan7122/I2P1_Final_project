#include "global.h"

// variables for global usage
const float FPS = 60.0;
const int WIDTH = 400;
const int HEIGHT = 600;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
bool key_state[ALLEGRO_KEY_MAX];
bool judge_next_window = false;
