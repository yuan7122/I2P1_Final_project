#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include "element.h"
/*
   [game scene object]
*/
typedef struct _GameScene
{
    ALLEGRO_BITMAP* background;
    Elements *ele_list[100];
    ALLEGRO_SAMPLE *sample;

}GameScene;
Scene* New_GameScene(char* label);
void game_scene_process(Scene* const pGameSceneObj, ALLEGRO_EVENT event);
void game_scene_update(Scene* const pGameSceneObj);
void game_scene_draw(Scene* const pGameSceneObj);
void game_scene_destroy(Scene* const pGameSceneObj);

#endif
