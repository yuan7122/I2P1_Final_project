#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED
#include "../global.h"
#include <stdbool.h>

typedef struct _Elements Elements;
typedef void (*fptrEleDraw)(Elements *);
typedef void (*fptrEleUpdate)(Elements *);
typedef void (*fptrEleInteract)(Elements *);
typedef void (*fptrEleDestroy)(Elements *);
struct _Elements
{
    int label; // the class of the element
    int id;    // the index in scene element list
    void *pDerivedObj;
    int inter_len;
    int inter_obj[MAX_ELEMENT]; // The label for the obj you want to interact
    bool dele;                  // If the object need to be deleted
    // interface for function
    fptrEleDraw Draw;
    fptrEleUpdate Update;
    fptrEleInteract Interact;
    fptrEleDestroy Destroy;
};
Elements *New_Elements(int label);

#endif
