#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include "element.h"
#include "charater.h"
#include "floor.h"
#include "teleport.h"
#include "tree.h"
#include "projectile.h"
/*
   [game scene object]
*/
enum
{
    Character_L=0,
    Floor_L,
    Teleport_L,
    Tree_L,
    Projectile_L
};
typedef struct _GameScene
{
    ALLEGRO_BITMAP* background;

} GameScene;
Scene* New_GameScene(int label);
void game_scene_process(Scene* const pGameSceneObj, ALLEGRO_EVENT event);
void game_scene_update(Scene* const pGameSceneObj);
void game_scene_draw(Scene* const pGameSceneObj);
void game_scene_destroy(Scene* const pGameSceneObj);

#endif
