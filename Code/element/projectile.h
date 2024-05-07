#ifndef Projectile_H_INCLUDED
#define Projectile_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Projectile object]
*/
typedef struct _Projectile
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of projectile
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Projectile;
Elements *New_Projectile(int label, int x, int y, int v);
void Projectile_update(Elements *const ele);
void Projectile_interact(Elements *const, Elements *const);
void Projectile_draw(Elements *const ele);
void Projectile_destory(Elements *const ele);
void _Projectile_update_position(Elements *const self, int dx, int dy);
#endif
