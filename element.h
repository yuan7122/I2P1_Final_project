#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED
#include "global.h"
typedef struct _Elements Elements;
typedef void    (*fptrEleProcess)(Elements* const, ALLEGRO_EVENT);
typedef void    (*fptrEleDraw)(Elements* const);
typedef void    (*fptrEleUpdate)(Elements* const);
typedef void    (*fptrEleDestroy)(Elements* const);
struct _Elements
{
    char* label;
    void* pDerivedObj;
    //interface for function
    fptrEleProcess Process;
    fptrEleDraw Draw;
    fptrEleUpdate Update;
    fptrEleDestroy Destroy;

};
Elements* New_Elements(char* label);

#endif
