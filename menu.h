#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "scene.h"
/*
   [Menu object]
*/
typedef struct _Menu
{
    ALLEGRO_FONT* font;
} Menu;
Scene* New_Menu(int label);
void menu_process(Scene* const pMenuObj, ALLEGRO_EVENT event);
void menu_update(Scene* const pMenuObj);
void menu_draw(Scene* const pMenuObj);
void menu_destroy(Scene* const pMenuObj);

#endif
