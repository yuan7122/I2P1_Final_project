#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include "scene.h"
/*
   [Menu object]
*/
typedef struct _Menu
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    int title_x, title_y;
} Menu;
Scene *New_Menu(int label);
void menu_update(Scene *self);
void menu_draw(Scene *self);
void menu_destroy(Scene *self);

#endif
