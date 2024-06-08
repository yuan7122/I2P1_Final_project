#ifndef Seeds_s_H_INCLUDED
#define Seeds_s_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Seeds_s object]
*/
typedef struct _Seeds_s
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of seeds_s
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Seeds_s;
Elements *New_Seeds_s(int label, int x, int y, int v);
void Seeds_s_update(Elements *self);
void Seeds_s_interact(Elements *self, Elements *tar);
void Seeds_s_draw(Elements *self);
void Seeds_s_destory(Elements *self);
void _Seeds_s_update_position(Elements *self, int dx, int dy);
#endif
