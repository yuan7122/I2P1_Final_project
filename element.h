#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED
#include "global.h"

typedef struct _Elements Elements;
typedef void    (*fptrEleProcess)(Elements* const, ALLEGRO_EVENT);
typedef void    (*fptrEleDraw)(Elements* const);
typedef void    (*fptrEleUpdate)(Elements* const);
typedef void    (*fptrEleInteract)(Elements* const, Elements* const);
typedef void    (*fptrEleDestroy)(Elements* const);
struct _Elements
{
    int label;
    void* pDerivedObj;
    int inter_len;
    int inter_obj[MAX_ELEMENT];
    //interface for function
    fptrEleProcess Process;
    fptrEleDraw Draw;
    fptrEleUpdate Update;
    fptrEleInteract Interact;
    fptrEleDestroy Destroy;
};
Elements* New_Elements(int label);

#endif
