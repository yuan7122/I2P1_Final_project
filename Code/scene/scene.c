#include "scene.h"
#include <stdbool.h>
/*
   [Scene function]
*/
void _Remove_elements(Scene *scene, Elements *ele)
{
    EPNode *ptr = scene->ele_list[ele->label];
    EPNode *parent_ptr = NULL;
    while (ptr)
    {
        if (ptr->id == ele->id)
        {
            if (parent_ptr == NULL)
            {
                scene->ele_list[ele->label] = ptr->next;
                free(ptr);
                break;
            }
            else
            {
                parent_ptr->next = ptr->next;
                free(ptr);
                break;
            }
        }
        parent_ptr = ptr;
        ptr = ptr->next;
    }
    scene->ele_num--;
}
void _Register_elements(Scene *scene, Elements *ele)
{
    EPNode *ptr = scene->ele_list[ele->label];
    EPNode *new_node = (EPNode *)malloc(sizeof(EPNode));
    new_node->id = scene->ele_num++;
    new_node->ele = ele;
    new_node->next = NULL;
    ele->id = new_node->id;
    if (ptr == NULL)
    {
        scene->ele_list[ele->label] = new_node;
    }
    else
    {
        while (ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = new_node;
    }
}

ElementVec _Get_all_elements(Scene *scene)
{
    ElementVec res;
    int size = 0;
    for (int i = 0; i < MAX_ELEMENT; i++)
    {
        if (scene->ele_list[i] == NULL)
            continue;
        EPNode *ptr = scene->ele_list[i];
        while (ptr)
        {
            res.arr[size++] = ptr->ele;
            ptr = ptr->next;
        }
        if (size == scene->ele_num)
            break;
    }
    res.len = scene->ele_num;
    return res;
}
ElementVec _Get_label_elements(Scene *scene, int label)
{
    EPNode *ptr = scene->ele_list[label];
    ElementVec res;
    int size = 0;
    while (ptr)
    {
        res.arr[size++] = ptr->ele;
        ptr = ptr->next;
    }
    res.len = size;
    return res;
}
Scene *New_Scene(int label)
{
    Scene *pObj;
    pObj = (Scene *)malloc(sizeof(Scene));
    // setting object member
    pObj->label = label;
    pObj->scene_end = false;
    pObj->ele_num = 0;
    for (int i = 0; i < MAX_ELEMENT; i++)
        pObj->ele_list[i] = NULL;
    pObj->pDerivedObj = pObj;
    return pObj;
}
