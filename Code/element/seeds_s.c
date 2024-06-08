#include "seeds_s.h"
#include "../shapes/Circle.h"
/*
   [Seeds_s function]
*/
//deleted int v. by lintzoe
Elements *New_Seeds_s(int label, int x, int y)
{
    Seeds_s *pDerivedObj = (Seeds_s *)malloc(sizeof(Seeds_s));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    
    pDerivedObj->img = al_load_bitmap("assets/image/seeds_s.webp");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // 初始化計時相關變量
    pDerivedObj->plant_time = al_get_time();
    pDerivedObj->is_harvestable = false;
    
    // setting the interact object
    /*pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;*/

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Seeds_s_update;
    pObj->Interact = Seeds_s_interact;
    pObj->Draw = Seeds_s_draw;
    pObj->Destroy = Seeds_s_destory;

    return pObj;
}
void Seeds_s_update(Elements *self)
{
    Seeds_s *Obj = ((Seeds_s *)(self->pDerivedObj));
    double current_time = al_get_time();
    double elapsed_time = current_time - Obj->plant_time;

    // 設定草莓成長時間為20秒
    if (elapsed_time >= 20.0) {
        Obj->is_harvestable = true;
    }
}
/*void _Seeds_s_update_position(Elements *self, int dx, int dy)
{
    Seeds_s *Obj = ((Seeds_s *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}*/
void Seeds_s_interact(Elements *self, Elements *tar)
{
    //Seeds_s *Obj = ((Seeds_s *)(self->pDerivedObj));
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
void Seeds_s_draw(Elements *self)
{
    Seeds_s *Obj = ((Seeds_s *)(self->pDerivedObj));
    //al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);

    if (Obj->is_harvestable) {
        // 繪製可收成的草莓（這裡可以根據需求修改顏色或圖片）
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(255, 255, 255), Obj->x, Obj->y, 0);
    } else {
        // 繪製成長中的草莓
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(128, 128, 128), Obj->x, Obj->y, 0);
    }
}
void Seeds_s_destory(Elements *self)
{
    Seeds_s *Obj = ((Seeds_s *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
