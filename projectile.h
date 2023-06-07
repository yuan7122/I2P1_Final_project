#ifndef Projectile_H_INCLUDED
#define Projectile_H_INCLUDED
#include "element.h"
#include "gamescene.h" // for element label

/*
   [Projectile object]
*/
typedef struct _Projectile
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int v; // the velocity of projectile
    ALLEGRO_BITMAP *img;
} Projectile;
Elements* New_Projectile(int label, int x, int y, int v);
void Projectile_process(Elements* const ele, ALLEGRO_EVENT event);
void Projectile_update(Elements* const ele);
void Projectile_interact(Elements* const, Elements* const);
void Projectile_draw(Elements* const ele);
void Projectile_destory(Elements* const ele);

#endif
