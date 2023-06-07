#include "gamescene.h"
/*
   [GameScene function]
*/
Scene* New_GameScene(int label)
{
    GameScene* pDerivedObj = (GameScene*)malloc(sizeof(GameScene));
    Scene* pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("./image/stage.jpg");
    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_Floor(Floor_L));
    _Register_elements(pObj, New_Teleport(Teleport_L));
    _Register_elements(pObj, New_Tree(Tree_L));
    _Register_elements(pObj, New_Character(Character_L));
    // setting derived object function
    pObj->Process = game_scene_process;
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}
void game_scene_process(Scene* const pGameSceneObj, ALLEGRO_EVENT event)
{
    for(int i = 0 ; i < pGameSceneObj->ele_len ; i++)
    {
        if(pGameSceneObj->ele_list[i] == NULL) continue;
        pGameSceneObj->ele_list[i]->Process(pGameSceneObj->ele_list[i], event);
    }
}
void game_scene_update(Scene* const pGameSceneObj)
{
    Elements** const ele_list = pGameSceneObj->ele_list;
    // update every element
    for(int i = 0 ; i < pGameSceneObj->ele_len ; i++)
    {
        if(ele_list[i] == NULL) continue;
        ele_list[i]->Update(ele_list[i]);
    }
    // interact the elements
    int *ele_pos = pGameSceneObj->ele_pos;
    // run every element
    for(int i = 0 ; i < pGameSceneObj->ele_len ; i++)
    {
        if(ele_list[i] == NULL) continue;
        // run every interact object
        for(int j = 0 ; j < ele_list[i]->inter_len; j++)
        {
            int inter_obj = ele_list[i]->inter_obj[j];
            if(ele_pos[inter_obj] != -1)
            {
                ele_list[i]->Interact(ele_list[i], ele_list[ele_pos[inter_obj]]);
                if(ele_list[i] == NULL) break;
            }
        }
    }
}
void game_scene_draw(Scene* const pGameSceneObj)
{
    al_clear_to_color(al_map_rgb(0,0,0));
    GameScene* gs = ((GameScene*)(pGameSceneObj->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    for(int i = 0 ; i < pGameSceneObj->ele_len ; i++)
    {
        if(pGameSceneObj->ele_list[i] == NULL) continue;
        pGameSceneObj->ele_list[i]->Draw(pGameSceneObj->ele_list[i]);
    }
}
void game_scene_destroy(Scene* const pGameSceneObj)
{
    GameScene* gs = ((GameScene*)(pGameSceneObj->pDerivedObj));
    ALLEGRO_BITMAP *background = gs->background;
    al_destroy_bitmap(background);
    for(int i = 0 ; i < pGameSceneObj->ele_len ; i++)
    {
        if(pGameSceneObj->ele_list[i] == NULL) continue;
        pGameSceneObj->ele_list[i]->Destroy(pGameSceneObj->ele_list[i]);
    }
}
