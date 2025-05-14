#ifndef Projectile_H_INCLUDED
#define Projectile_H_INCLUDED
#include "element.h"
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
void Projectile_update(Elements *self);
void Projectile_interact(Elements *self);
void Projectile_draw(Elements *self);
void Projectile_destory(Elements *self);
void _Projectile_update_position(Elements *self, int dx, int dy);
void _Projectile_interact_Floor(Elements *self, Elements *tar);
void _Projectile_interact_Tree(Elements *self, Elements *tar);

#endif
