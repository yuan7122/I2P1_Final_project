#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#define GAME_TERMINATE -1
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#define debug(x) if(x){printf("check at line number %d in file %s\n", __LINE__, __FILE__);}
#define MAX_ELEMENT 100
// note that you can't assign initial value for extern variable!
extern const double FPS;
extern const int WIDTH;
extern const int HEIGHT;
extern int window;
extern bool key_state[ALLEGRO_KEY_MAX];
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *fps;
extern bool debug_mode;


#endif
