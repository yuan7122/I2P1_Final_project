#include "seeds_s.h"
#include "../shapes/Circle.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdbool.h>
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
    pDerivedObj->score = 20;  // 初始化積分值
    pDerivedObj->font = al_create_builtin_font(); // 初始化字型
    pDerivedObj->timer = al_create_timer(1.0);
    pDerivedObj->countdown = 160;
    pDerivedObj->event_queue = al_create_event_queue();
    al_register_event_source(pDerivedObj->event_queue, al_get_timer_event_source(pDerivedObj->timer));
    al_start_timer(pDerivedObj->timer);
    
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
    ALLEGRO_EVENT ev;
    while (al_get_next_event(Obj->event_queue, &ev)) { // 獲取下一個事件
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            double current_time = al_get_time();
            double elapsed_time = current_time - Obj->plant_time;

            if (elapsed_time >= 160.0) {
                Obj->is_harvestable = true;
            }
            if (Obj->countdown > 0) {
                Obj->countdown = 160 - (int)elapsed_time;
                if (Obj->countdown <= 0) {
                    Obj->countdown = 0;
                    Obj->is_harvestable = true;
                }
            }
        }
    }
}
void Seeds_s_interact(Elements *self, Elements *tar)
{
    Seeds_s *Obj = ((Seeds_s *)(self->pDerivedObj));
    if (tar->label == Character_L && Obj->is_harvestable) {
        Obj->score += 5; // 收成後增加積分
        Obj->is_harvestable = false; // 重置為不可收成狀態
        Obj->plant_time = al_get_time(); // 重置種植時間
        Obj->countdown = 160; // 重置倒數時間
        al_start_timer(Obj->timer); // 重啟計時器
    }
}
// 修改 Seeds_s 的繪製函數
void Seeds_s_draw(Elements *self) 
{
    Seeds_s *Obj = ((Seeds_s *)(self->pDerivedObj));
    if (Obj->is_harvestable) {
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(255, 255, 255), Obj->x, Obj->y, 0);
    } else {
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(128, 128, 128), Obj->x, Obj->y, 0);
    }
    ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);
    al_draw_textf(Obj->font, text_color, Obj->x + Obj->width / 2, Obj->y + 20 + Obj->height, ALLEGRO_ALIGN_CENTER, "Score: %d", Obj->score);
    al_draw_textf(Obj->font, text_color, Obj->x + Obj->width / 2, Obj->y - 20, ALLEGRO_ALIGN_CENTER, "Time: %d", Obj->countdown);
}

void Seeds_s_destory(Elements *self) 
{
    Seeds_s *obj = (Seeds_s *)(self->pDerivedObj);
    al_destroy_bitmap(obj->img);
    free(obj->hitbox);
    al_destroy_font(obj->font);
    al_destroy_timer(obj->timer);
    al_destroy_event_queue(obj->event_queue);
    free(obj);
    free(self);
}