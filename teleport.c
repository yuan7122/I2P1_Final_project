#include "teleport.h"
/*
   [teleport function]
*/
Elements* New_Teleport(int label)
{
    Teleport* pDerivedObj = (Teleport*)malloc(sizeof(Teleport));
    Elements* pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("./image/teleport.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = WIDTH - pDerivedObj->width;
    pDerivedObj->y = HEIGHT - pDerivedObj->height;
    pDerivedObj->activate = false;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Process = Teleport_process;
    pObj->Update = Teleport_update;
    pObj->Interact = Teleport_interact;
    pObj->Draw = Teleport_draw;
    pObj->Destroy = Teleport_destory;
    return pObj;
}
void Teleport_process(Elements* const ele, ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_DOWN )
    {
        key_state[event.keyboard.keycode] = true;
    }
    else if( event.type == ALLEGRO_EVENT_KEY_UP )
    {
        key_state[event.keyboard.keycode] = false;
    }
}
void Teleport_update(Elements* const ele)
{
    Teleport* Obj = ((Teleport*)(ele->pDerivedObj));
    if( key_state[ALLEGRO_KEY_W] )
    {
        Obj->activate = true;
    }
    else
    {
        Obj->activate = false;
    }
}
void Teleport_interact(Elements* const self_ele, Elements* const ele)
{
    if(ele->label == Character_L)
    {
        Character *chara = (Character*)(ele->pDerivedObj);
        Teleport *Obj = (Teleport*)(self_ele->pDerivedObj);
        if( chara->x >= Obj->x &&
                chara->x <= Obj->x + Obj->width &&
                Obj->activate
          ) chara->x = 0;
    }
}
void Teleport_draw(Elements* const ele)
{
    Teleport *Obj = ((Teleport*)(ele->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Teleport_destory(Elements* const ele)
{
    Teleport *Obj = ((Teleport*)(ele->pDerivedObj));
    al_destroy_bitmap(Obj->img);
}
