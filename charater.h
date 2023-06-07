#ifndef CHARATER_H_INCLUDED
#define CHARATER_H_INCLUDED
#include "element.h"
#include "scene.h"
#include "projectile.h"

/*
   [character object]
*/
enum {STOP = 0, MOVE, ATK};
typedef struct _Character
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[2];
    ALLEGRO_BITMAP *img_atk[2];
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
    bool new_proj;
} Character;
Elements* New_Character(int label);
void Character_process(Elements* const ele, ALLEGRO_EVENT event);
void Character_update(Elements* const self_ele);
void Character_interact(Elements* const, Elements* const);
void Character_draw(Elements* const ele);
void Character_destory(Elements* const ele);

#endif
