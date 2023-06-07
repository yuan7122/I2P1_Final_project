#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED
#include "global.h"
// include scene and following component
#include "scene.h"
#include "menu.h"
#include "gamescene.h"
// include element and following component
#include "element.h"
#include "charater.h"
#include "floor.h"
#include "teleport.h"
#include "tree.h"

int Game_establish();
void game_init();
void game_begin();
void game_update();
int process_event();
void game_draw();
int game_run();
void game_destroy();

#endif
