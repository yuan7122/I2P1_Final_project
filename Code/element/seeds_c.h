#ifndef Seeds_c_H_INCLUDED
#define Seeds_c_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_font.h>
/*
   [Seeds_c object]
*/
typedef struct _Seeds_c
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
    // 添加計時相關變量
    double plant_time;
    bool is_harvestable;
    // 添加積分值變量
    int score; 
    // 新增成員變數
    ALLEGRO_FONT *font;
} Seeds_c;
Elements *New_Seeds_c(int label, int x, int y);
void Seeds_c_update(Elements *self);
void Seeds_c_interact(Elements *self, Elements *tar);
void Seeds_c_draw(Elements *self);
void Seeds_c_destory(Elements *self);
void _Seeds_c_update_position(Elements *self, int dx, int dy);
#endif
