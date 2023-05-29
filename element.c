#include "element.h"
/*
   [Element function]
*/
Elements* New_Elements(char* label){
    Elements* pObj;
    pObj = (Elements*)malloc(sizeof(Elements));
    // setting object member
    pObj->label = (char*)malloc(sizeof(char)*(strlen(label)+1));
    strcpy(pObj->label, label);
    pObj->pDerivedObj = pObj;
    return pObj;
}
