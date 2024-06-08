#include "Seeds_e.h"
#include "../shapes/Circle.h"
/*
   [Seeds_e function]
*/
//deleted int v. by lintzoe
Elements *New_Seeds_e(int label, int x, int y)
{
    Seeds_e *pDerivedObj = (Seeds_e *)malloc(sizeof(Seeds_e));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    
    pDerivedObj->img = al_load_bitmap("assets/image/seeds_e.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    //pDerivedObj->v = v;
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // setting the interact object
    /*pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;*/
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Seeds_e_update;
    pObj->Interact = Seeds_e_interact;
    pObj->Draw = Seeds_e_draw;
    pObj->Destroy = Seeds_e_destory;

    return pObj;
}
void Seeds_e_update(Elements *self)
{
    Seeds_e *Obj = ((Seeds_e *)(self->pDerivedObj));
    _Seeds_e_update_position(self, Obj->v, 0);
}
void _Seeds_e_update_position(Elements *self, int dx, int dy)
{
    /*Seeds_e *Obj = ((Seeds_e *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);*/
}
void Seeds_e_interact(Elements *self, Elements *tar)
{
    //Seeds_e *Obj = ((Seeds_e *)(self->pDerivedObj));
    /*if (tar->label == Floor_L)
    {
        if (Obj->x < 0 - Obj->width)
            self->dele = true;
        else if (Obj->x > WIDTH + Obj->width)
            self->dele = true;
    }
    else if (tar->label == Tree_L)
    {
        Tree *tree = ((Tree *)(tar->pDerivedObj));
        if (tree->hitbox->overlap(tree->hitbox, Obj->hitbox))
        {
            self->dele = true;
        }
    }*/
}
void Seeds_e_draw(Elements *self)
{
    Seeds_e *Obj = ((Seeds_e *)(self->pDerivedObj));
    if (Obj->v > 0)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Seeds_e_destory(Elements *self)
{
    Seeds_e *Obj = ((Seeds_e *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
