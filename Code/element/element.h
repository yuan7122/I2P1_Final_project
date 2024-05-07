#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED
#include "../global.h"

typedef struct _Elements Elements;
typedef void (*fptrEleDraw)(Elements *const);
typedef void (*fptrEleUpdate)(Elements *const);
typedef void (*fptrEleInteract)(Elements *const, Elements *const);
typedef void (*fptrEleDestroy)(Elements *const);
struct _Elements
{
    int label; // the class of the element
    int id; // the index in scene element list
    void *pDerivedObj;
    int inter_len;
    int inter_obj[MAX_ELEMENT];
    bool dele;
    // interface for function
    fptrEleDraw Draw;
    fptrEleUpdate Update;
    fptrEleInteract Interact;
    fptrEleDestroy Destroy;
};
Elements *New_Elements(int label);

#endif
