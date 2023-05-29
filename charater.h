#ifndef CHARATER_H_INCLUDED
#define CHARATER_H_INCLUDED
#include "global.h"
#include "element.h"

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
}Character;
Elements* New_Character(char* label);
void charater_process(Elements* const ele, ALLEGRO_EVENT event);
void charater_update(Elements* const self_ele);
void character_draw(Elements* const ele);
void character_destory(Elements* const ele);

#endif
