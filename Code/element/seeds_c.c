#include "Seeds_c.h"
#include "../shapes/Circle.h"
/*
   [Seeds_c function]
*/
//deleted int v. by lintzoe
Elements *New_Seeds_c(int label, int x, int y)
{
    Seeds_c *pDerivedObj = (Seeds_c *)malloc(sizeof(Seeds_c));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    
    pDerivedObj->img = al_load_bitmap("assets/image/seeds_c.webp");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    //pDerivedObj->v = v;
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
    pObj->Update = Seeds_c_update;
    pObj->Interact = Seeds_c_interact;
    pObj->Draw = Seeds_c_draw;
    pObj->Destroy = Seeds_c_destory;

    return pObj;
}
void Seeds_c_update(Elements *self)
{
    Seeds_c *Obj = ((Seeds_c *)(self->pDerivedObj));
    double current_time = al_get_time();
    double elapsed_time = current_time - Obj->plant_time;

    // 設定草莓成長時間為20秒
    if (elapsed_time >= 20.0) {
        Obj->is_harvestable = true;
    }
}
void _Seeds_c_update_position(Elements *self, int dx, int dy)
{
    
}
void Seeds_c_interact(Elements *self, Elements *tar)
{
    //Seeds_c *Obj = ((Seeds_c *)(self->pDerivedObj));
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
void Seeds_c_draw(Elements *self)
{
    Seeds_c *Obj = ((Seeds_c *)(self->pDerivedObj));
    if (Obj->is_harvestable) {
        // 繪製可收成的草莓（這裡可以根據需求修改顏色或圖片）
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(255, 255, 255), Obj->x, Obj->y, 0);
    } else {
        // 繪製成長中的草莓
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(128, 128, 128), Obj->x, Obj->y, 0);
    }
}
void Seeds_c_destory(Elements *self)
{
    Seeds_c *Obj = ((Seeds_c *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
