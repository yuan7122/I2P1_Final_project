#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED
#include "global.h"
#include "element.h"
#include "charater.h"
#include "scene.h"
#include "gamescene.h"
#include "menu.h"

int Game_establish();
void game_init();
void game_begin();
void game_update();
int process_event();
void game_draw();
int game_run();
void game_destroy();

#endif
