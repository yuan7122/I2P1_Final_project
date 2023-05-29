#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED
#include "global.h"
#include "charater.h"

/*
   [scene object]
*/
typedef struct _Scene Scene;
typedef void    (*fptrProcess)(Scene* const, ALLEGRO_EVENT);
typedef void    (*fptrUpdate)(Elements* const);
typedef void    (*fptrDraw)(Scene* const);
typedef void    (*fptrDestroy)(Scene* const);
struct _Scene
{
    char* label;
    void* pDerivedObj;
    bool scene_end;
    int len;
    //interface for function
    fptrProcess Process;
    fptrUpdate Update;
    fptrDraw Draw;
    fptrDestroy Destroy;
};
Scene* New_Scene(char* label);




#endif
