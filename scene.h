#include "global.h"
#include "charater.h"

void menu_init();
void menu_process(ALLEGRO_EVENT event);
void menu_draw();
void menu_destroy();

void game_scene_init();
void game_scene_draw();
void game_scene_destroy();

// structure to represent ground
typedef struct t_pos {
    int type;
    int x;
    int y;
    int nWidth;
    int nHeight;
} Pos;

