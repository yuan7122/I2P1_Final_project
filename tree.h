#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include "element.h"
#include "gamescene.h" // for element label
/*
   [tree object]
*/
typedef struct _Tree
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
} Tree;
Elements* New_Tree(int label);
void Tree_process(Elements* const ele, ALLEGRO_EVENT event);
void Tree_update(Elements* const ele);
void Tree_interact(Elements* const, Elements* const);
void Tree_draw(Elements* const ele);
void Tree_destory(Elements* const ele);

#endif
