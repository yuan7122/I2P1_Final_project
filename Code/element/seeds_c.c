#include "seeds_c.h"
#include "../shapes/Circle.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdbool.h>
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
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // 初始化計時相關變量
    pDerivedObj->plant_time = al_get_time();
    pDerivedObj->is_harvestable = false;
    pDerivedObj->score = 5;  // 初始化積分值
    pDerivedObj->font = al_create_builtin_font(); // 初始化字型

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

    // 設定玉米成長時間為20秒
    if (elapsed_time >= 20.0) {
        Obj->is_harvestable = true;
    }
    // 設定倒數時間
    Obj->countdown = 20 - (int)elapsed_time;

}
void Seeds_c_interact(Elements *self, Elements *tar)
{
    /*Seeds_c *Obj = ((Seeds_c *)(self->pDerivedObj));
    // 如果主要角色與玉米互動，且玉米可收成，則執行收成動作
    if (tar->label == Player_L && Obj->is_harvestable) {
        // 執行收成動作，可根據需求填寫
        Obj->score += 5;  // 假設每次收成都增加積分
        Obj->is_harvestable = false;  // 收成後重新設置為不可收成狀態
    }*/
}
// 修改 Seeds_c 的繪製函數
void Seeds_c_draw(Elements *self) 
{
    Seeds_c *Obj = ((Seeds_c *)(self->pDerivedObj));
    if (Obj->is_harvestable) {
        // 繪製可收成的玉米（這裡可以根據需求修改顏色或圖片）
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(255, 255, 255), Obj->x, Obj->y, 0);
    } else {
        // 繪製成長中的玉米
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(128, 128, 128), Obj->x, Obj->y, 0);
    }
    // 顯示積分值
    ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);
    al_draw_textf(Obj->font, text_color, Obj->x + Obj->width / 2, Obj->y + Obj->height, ALLEGRO_ALIGN_CENTER, "Score: %d", Obj->score);

    // 顯示倒數時間
    al_draw_textf(Obj->font, text_color, Obj->x + Obj->width / 2, Obj->y - 20, ALLEGRO_ALIGN_CENTER, "Time: %d", Obj->countdown);
}

void Seeds_c_destory(Elements *self) 
{
    Seeds_c *obj = (Seeds_c *)(self->pDerivedObj);
    al_destroy_bitmap(obj->img);
    free(obj->hitbox);
    al_destroy_font(obj->font);  // 釋放字型資源
    free(obj);
    free(self);
}