#include "tree.h"
/*
   [tree function]
*/
Elements* New_Tree(int label)
{
    Tree* pDerivedObj = (Tree*)malloc(sizeof(Tree));
    Elements* pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("./image/tree.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 85;
    pDerivedObj->y = HEIGHT - pDerivedObj->height;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Process = Tree_process;
    pObj->Update = Tree_update;
    pObj->Interact = Tree_interact;
    pObj->Draw = Tree_draw;
    pObj->Destroy = Tree_destory;
    return pObj;
}
void Tree_process(Elements* const ele, ALLEGRO_EVENT event) {}
void Tree_update(Elements* const ele) {}
void Tree_interact(Elements* const self_ele, Elements* const ele) {}
void Tree_draw(Elements* const ele)
{
    Tree *Obj = ((Tree*)(ele->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Tree_destory(Elements* const ele)
{
    Tree *Obj = ((Tree*)(ele->pDerivedObj));
    al_destroy_bitmap(Obj->img);
}
