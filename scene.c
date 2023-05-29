#include "scene.h"
/*
   [Scene function]
*/
Scene* New_Scene(char* label){
    Scene *pObj;
    pObj = (Scene*)malloc(sizeof(Scene));
    // setting object member
    pObj->label = (char*)malloc(sizeof(char)*(strlen(label)+1));
    strcpy(pObj->label, label);
    pObj->scene_end = false;
    pObj->len = 0;
    pObj->pDerivedObj = pObj;
    return pObj;
}




