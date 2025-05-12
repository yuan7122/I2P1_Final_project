#include "element.h"
#include <stdbool.h>
/*
   [Element function]
*/
Elements *New_Elements(int label)
{
    Elements *pObj;
    pObj = (Elements *)malloc(sizeof(Elements));
    pObj->inter_len = 0;
    pObj->dele = false;
    // setting object member
    pObj->label = label;
    pObj->pDerivedObj = pObj;
    return pObj;
}
