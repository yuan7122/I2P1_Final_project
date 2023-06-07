#include "projectile.h"
/*
   [Projectile function]
*/
Elements* New_Projectile(int label, int x, int y, int v)
{
    Projectile* pDerivedObj = (Projectile*)malloc(sizeof(Projectile));
    Elements* pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("./image/projectile.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->v = v;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Process = Projectile_process;
    pObj->Update = Projectile_update;
    pObj->Interact = Projectile_interact;
    pObj->Draw = Projectile_draw;
    pObj->Destroy = Projectile_destory;
    return pObj;
}
void Projectile_process(Elements* const ele, ALLEGRO_EVENT event) {}
void Projectile_update(Elements* const ele)
{
    Projectile *Obj = ((Projectile*)(ele->pDerivedObj));
    Obj->x += Obj->v;
}
void Projectile_interact(Elements* const self_ele, Elements* const ele)
{
    Projectile *Obj = ((Projectile*)(self_ele->pDerivedObj));
    if(ele->label == Floor_L)
    {
        if(Obj->x < 0 - Obj->width) _Remove_elements(scene, self_ele);
        else if(Obj->x > WIDTH + Obj->width) _Remove_elements(scene, self_ele);

    }
    else if(ele->label == Tree_L)
    {
        Tree* tree = ((Tree*)(ele->pDerivedObj));
        if(Obj->x + Obj->width/2 >= tree->x + 75 && Obj->x + Obj->width/2 <= tree->x + tree->width - 75)
            _Remove_elements(scene, self_ele);
    }
}
void Projectile_draw(Elements* const ele)
{
    Projectile *Obj = ((Projectile*)(ele->pDerivedObj));
    if(Obj->v > 0)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Projectile_destory(Elements* const ele)
{
    Projectile *Obj = ((Projectile*)(ele->pDerivedObj));
    al_destroy_bitmap(Obj->img);
}
