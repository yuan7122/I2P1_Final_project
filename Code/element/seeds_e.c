#include "seeds_e.h"
#include "../shapes/Circle.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdbool.h>
/*
   [Seeds_e function]
*/
//deleted int v. by lintzoe
Elements *New_Seeds_e(int label, int x, int y)
{
    Seeds_e *pDerivedObj = (Seeds_e *)malloc(sizeof(Seeds_e));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    
    pDerivedObj->img = al_load_bitmap("assets/image/seeds_e.webp");
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
    pDerivedObj->score = 10;  // 初始化積分值
    // 初始化字型
    pDerivedObj->font = al_create_builtin_font();

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
    double current_time = al_get_time();
    double elapsed_time = current_time - Obj->plant_time;

    // 設定茄子成長時間為20秒
    if (elapsed_time >= 20.0) {
        Obj->is_harvestable = true;
    }
}
/*void _Seeds_e_update_position(Elements *self, int dx, int dy)
{
}*/
void Seeds_e_interact(Elements *self, Elements *tar)
{
}
// 修改 Seeds_e 的繪製函數
void Seeds_e_draw(Elements *self) 
{
    Seeds_e *Obj = ((Seeds_e *)(self->pDerivedObj));
    if (Obj->is_harvestable) {
        // 繪製可收成的茄子（這裡可以根據需求修改顏色或圖片）
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(255, 255, 255), Obj->x, Obj->y, 0);
    } else {
        // 繪製成長中的茄子
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(128, 128, 128), Obj->x, Obj->y, 0);
    }
    // 只在字型存在時才使用
    if (Obj->font) {
        ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);
        al_draw_textf(Obj->font, text_color, Obj->x + Obj->width / 2, Obj->y - 20, ALLEGRO_ALIGN_CENTER, "%d", Obj->score);
    }
}

void Seeds_e_destory(Elements *self) 
{
    Seeds_e *obj = (Seeds_e *)(self->pDerivedObj);
    al_destroy_bitmap(obj->img);
    free(obj->hitbox);
    al_destroy_font(obj->font);  // 釋放字型資源
    free(obj);
    free(self);
}