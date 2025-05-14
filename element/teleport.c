#include "teleport.h"
#include "../scene/gamescene.h" // for element label
#include "../scene/sceneManager.h" // for scene variable
#include "charater.h"
#include <stdbool.h>
/*
   [teleport function]
*/
Elements *New_Teleport(int label)
{
    Teleport *pDerivedObj = (Teleport *)malloc(sizeof(Teleport));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/teleport.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = WIDTH - pDerivedObj->width;
    pDerivedObj->y = HEIGHT - pDerivedObj->height;
    pDerivedObj->activate = false;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Teleport_update;
    pObj->Interact = Teleport_interact;
    pObj->Draw = Teleport_draw;
    pObj->Destroy = Teleport_destory;
    return pObj;
}
void Teleport_update(Elements *self)
{
    Teleport *Obj = ((Teleport *)(self->pDerivedObj));
    if (key_state[ALLEGRO_KEY_W])
    {
        Obj->activate = true;
    }
    else
    {
        Obj->activate = false;
    }
}
void Teleport_interact(Elements *self)
{
    ElementVec labelEle = _Get_label_elements(scene, Character_L);
    for (int i = 0; i < labelEle.len; i++)
    {
        _Teleport_interact_Character(self, labelEle.arr[i]);
    }
}
void _Teleport_interact_Character(Elements *self, Elements *tar)
{
    Character *chara = (Character *)(tar->pDerivedObj);
    Teleport *Obj = (Teleport *)(self->pDerivedObj);
    if (chara->x >= Obj->x &&
        chara->x <= Obj->x + Obj->width &&
        Obj->activate)
    {
        _Character_update_position(tar, 0 - chara->x, 0);
    }
}
void Teleport_draw(Elements *self)
{
    Teleport *Obj = ((Teleport *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Teleport_destory(Elements *self)
{
    Teleport *Obj = ((Teleport *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
