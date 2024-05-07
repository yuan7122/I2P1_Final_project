#ifndef TELEPORT_H_INCLUDED
#define TELEPORT_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
/*
   [teleport object]
*/
typedef struct _Teleport
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    bool activate;
} Teleport;
Elements *New_Teleport(int label);
void Teleport_update(Elements *const ele);
void Teleport_interact(Elements *const, Elements *const);
void Teleport_draw(Elements *const ele);
void Teleport_destory(Elements *const ele);

#endif
