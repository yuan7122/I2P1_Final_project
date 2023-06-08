#include "scene.h"
/*
   [Scene function]
*/
Scene* New_Scene(int label)
{
    Scene *pObj;
    pObj = (Scene*)malloc(sizeof(Scene));
    // setting object member
    pObj->label = label;
    pObj->scene_end = false;
    pObj->ele_len = 0;
    pObj->ele_num = 0;
    for(int i = 0 ; i < MAX_ELEMENT ; i++) pObj->ele_pos[i] = -1;
    for(int i = 0 ; i < MAX_ELEMENT ; i++) pObj->ele_list[i] = NULL;
    pObj->pDerivedObj = pObj;
    return pObj;
}
void _Register_elements(Scene* const scene, Elements* const ele)
{
    scene->ele_list[scene->ele_len] = ele;
    scene->ele_pos[ele->label] = scene->ele_len;
    scene->ele_len++;
    scene->ele_num++;
}
void _Remove_elements(Scene* const scene, int index)
{
    scene->ele_num--;
    scene->ele_pos[scene->ele_list[index]->label] = -1;
    scene->ele_list[index]->Destroy(scene->ele_list[index]);
    scene->ele_list[index] = NULL;
    if(scene->ele_num <= scene->ele_len/2)
    {
        Elements *temp_ele_list[MAX_ELEMENT];
        int ind = 0;
        for(int i = 0 ; i < scene->ele_len ; i++)
        {
            if(scene->ele_list[i] != NULL)
            {
                temp_ele_list[ind++] = scene->ele_list[i];
            }
        }
        for(int i = 0 ; i < ind ; i++)
        {
            scene->ele_list[i] = temp_ele_list[i];
            scene->ele_pos[temp_ele_list[i]->label] = i;
        }
        scene->ele_len = ind;
    }
}



