#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED
#include "global.h"
#include "element.h"

/*
   [scene object]
*/
enum
{
    Menu_L = 0,
    GameScene_L
};
typedef struct _Scene Scene;
typedef void    (*fptrProcess)(Scene* const, ALLEGRO_EVENT);
typedef void    (*fptrUpdate)(Scene* const);
typedef void    (*fptrDraw)(Scene* const);
typedef void    (*fptrDestroy)(Scene* const);
struct _Scene
{
    int label;
    void* pDerivedObj;
    bool scene_end;
    int ele_len;
    int ele_num;
    Elements *ele_list[MAX_ELEMENT];
    int ele_pos[MAX_ELEMENT];
    //interface for function
    fptrProcess Process;
    fptrUpdate Update;
    fptrDraw Draw;
    fptrDestroy Destroy;
};
extern Scene* scene;
Scene* New_Scene(int label);
void _Register_elements(Scene* const, Elements* const);
void _Remove_elements(Scene* const, int);




#endif
