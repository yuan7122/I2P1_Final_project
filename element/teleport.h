#ifndef TELEPORT_H_INCLUDED
#define TELEPORT_H_INCLUDED
#include "element.h"
#include <stdbool.h>
/*
   [teleport object]
*/
typedef struct _Teleport
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    bool activate; // If the teleport be activated
} Teleport;
Elements *New_Teleport(int label);
void Teleport_update(Elements *self);
void Teleport_interact(Elements *self);
void Teleport_draw(Elements *self);
void Teleport_destory(Elements *self);
void _Teleport_interact_Character(Elements *self, Elements *tar);

#endif
