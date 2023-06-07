#include "element.h"
/*
   [Element function]
*/
Elements* New_Elements(int label)
{
    Elements* pObj;
    pObj = (Elements*)malloc(sizeof(Elements));
    pObj->inter_len = 0;
    // setting object member
    pObj->label = label;
    pObj->pDerivedObj = pObj;
    return pObj;
}
