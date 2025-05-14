#include "tree.h"
#include "../shapes/Rectangle.h"
/*
   [tree function]
*/
Elements *New_Tree(int label)
{
    Tree *pDerivedObj = (Tree *)malloc(sizeof(Tree));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/tree.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 85;
    pDerivedObj->y = HEIGHT - pDerivedObj->height;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Tree_update;
    pObj->Interact = Tree_interact;
    pObj->Draw = Tree_draw;
    pObj->Destroy = Tree_destory;
    return pObj;
}
void Tree_update(Elements *self) {}
void Tree_interact(Elements *self) {}
void Tree_draw(Elements *self)
{
    Tree *Obj = ((Tree *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Tree_destory(Elements *self)
{
    Tree *Obj = ((Tree *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
