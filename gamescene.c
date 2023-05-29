#include "gamescene.h"
/*
   [GameScene function]
*/
Scene* New_GameScene(char* label){
    GameScene* pDerivedObj = (GameScene*)malloc(sizeof(GameScene));
    Scene* pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("./image/stage.jpg");
    pDerivedObj->ele_list[pObj->len++] = New_Character("Character");
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Process = game_scene_process;
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}
void game_scene_process(Scene* const pGameSceneObj, ALLEGRO_EVENT event){
    GameScene* gs = ((GameScene*)(pGameSceneObj->pDerivedObj));
    for(int i = 0 ; i < pGameSceneObj->len ; i++){
        gs->ele_list[i]->Process(gs->ele_list[i], event);
    }
}
void game_scene_update(Scene* const pGameSceneObj){
    GameScene* gs = ((GameScene*)(pGameSceneObj->pDerivedObj));
    for(int i = 0 ; i < pGameSceneObj->len ; i++){
        gs->ele_list[i]->Update(gs->ele_list[i]);
    }
}
void game_scene_draw(Scene* const pGameSceneObj){
    al_clear_to_color(al_map_rgb(0,0,0));
    GameScene* gs = ((GameScene*)(pGameSceneObj->pDerivedObj));
    ALLEGRO_BITMAP *background = gs->background;
    al_draw_bitmap(background, 0, 0, 0);
    for(int i = 0 ; i < pGameSceneObj->len ; i++){
        gs->ele_list[i]->Draw(gs->ele_list[i]);
    }
}
void game_scene_destroy(Scene* const pGameSceneObj){
    GameScene* gs = ((GameScene*)(pGameSceneObj->pDerivedObj));
    ALLEGRO_BITMAP *background = gs->background;
    al_destroy_bitmap(background);
    for(int i = 0 ; i < pGameSceneObj->len ; i++){
        gs->ele_list[i]->Destroy(gs->ele_list[i]);
    }
}
