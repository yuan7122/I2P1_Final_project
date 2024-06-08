#ifndef Seeds_c_H_INCLUDED
#define Seeds_c_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Seeds_c object]
*/
typedef struct _Seeds_c
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of seeds_c
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Seeds_c;
Elements *New_Seeds_c(int label, int x, int y);
void Seeds_c_update(Elements *self);
void Seeds_c_interact(Elements *self, Elements *tar);
void Seeds_c_draw(Elements *self);
void Seeds_c_destory(Elements *self);
void _Seeds_c_update_position(Elements *self, int dx, int dy);
#endif
