#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED
#include "../global.h"
#include "../element/element.h"
#include <stdbool.h>

/*
   [scene object]
*/
typedef struct EPNode
{
    int id;
    Elements *ele;
    struct EPNode *next;
} EPNode;
typedef struct Element_vector
{
    Elements *arr[MAX_ELEMENT];
    int len;
} ElementVec;
typedef struct _Scene Scene;
typedef void (*fptrUpdate)(Scene *);
typedef void (*fptrDraw)(Scene *);
typedef void (*fptrDestroy)(Scene *);
struct _Scene
{
    int label;
    void *pDerivedObj;
    bool scene_end;
    int ele_num;
    EPNode *ele_list[MAX_ELEMENT];
    // interface for function
    fptrUpdate Update;
    fptrDraw Draw;
    fptrDestroy Destroy;
};
Scene *New_Scene(int label);
void _Register_elements(Scene *scene, Elements *ele);
void _Remove_elements(Scene *scene, Elements *ele);
ElementVec _Get_all_elements(Scene *scene);
ElementVec _Get_label_elements(Scene *scene, int label);
#endif
