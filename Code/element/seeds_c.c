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

// 全局標誌變量
bool interaction_processed = false;

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
    pDerivedObj->timer = al_create_timer(1.0);
    pDerivedObj->countdown = 20;
    pDerivedObj->event_queue = al_create_event_queue();
    pDerivedObj->is_processed = false; // 添加这个标志

    al_register_event_source(pDerivedObj->event_queue, al_get_timer_event_source(pDerivedObj->timer));
    al_start_timer(pDerivedObj->timer);
    
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;

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
    ALLEGRO_EVENT ev;
    while (al_get_next_event(Obj->event_queue, &ev)) { // 獲取下一個事件
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            double current_time = al_get_time();
            double elapsed_time = current_time - Obj->plant_time;

            if (elapsed_time >= 20.0) {
                Obj->is_harvestable = true;
            }
            if (Obj->countdown > 0) {
                Obj->countdown = 20 - (int)elapsed_time;
                if (Obj->countdown <= 0) {
                    Obj->countdown = 0;
                    Obj->is_harvestable = true;
                }
            }
        }

    }
    // 在每次更新後重置全局標誌
    interaction_processed = false;
}
void Seeds_c_interact(Elements *self, Elements *tar)
{
    Seeds_c *Obj = ((Seeds_c *)(self->pDerivedObj));
    if (tar->label == Character_L && Obj->is_harvestable && key_state[ALLEGRO_KEY_H]) {
        Character *chara = (Character *)(tar->pDerivedObj);
        
        // 確保物件已標記為可刪除以避免多次計分
        if (self->dele) {
            return;
        }

        // 碰撞檢測
        if (chara->hitbox->overlap(chara->hitbox, Obj->hitbox)) {
            self->dele = true;
            tot_score += Obj->score;
            Obj->is_processed = true; // 设置为已处理
            interaction_processed = true; // 设置全局标志为已处理
            printf("Harvested! Score added: %d, Total score: %d\n", Obj->score, tot_score);
            Obj->is_harvestable = false;
            Obj->plant_time = al_get_time();
            Obj->countdown = 20;
            al_start_timer(Obj->timer);
        }
        else{
            printf("No collision detected\n");
        }
    }
}
// 修改 Seeds_c 的繪製函數
void Seeds_c_draw(Elements *self) 
{
    Seeds_c *Obj = ((Seeds_c *)(self->pDerivedObj));
    if (Obj->is_harvestable) {
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(255, 255, 255), Obj->x, Obj->y-30, 0);
    } else {
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(128, 128, 128), Obj->x, Obj->y-30, 0);
    }
    ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);
    al_draw_textf(Obj->font, text_color, Obj->x + Obj->width / 2, Obj->y + Obj->height-30, ALLEGRO_ALIGN_CENTER, "Score: %d", Obj->score);
    al_draw_textf(Obj->font, text_color, Obj->x + Obj->width / 2, Obj->y - 40, ALLEGRO_ALIGN_CENTER, "Time: %d", Obj->countdown);
}

void Seeds_c_destory(Elements *self) 
{
    Seeds_c *obj = (Seeds_c *)(self->pDerivedObj);
    if (obj->img) {
        al_destroy_bitmap(obj->img);
    }
    if (obj->hitbox) {
        free(obj->hitbox);
    }
    if (obj->font) {
        al_destroy_font(obj->font);
    }
    if (obj->timer) {
        al_destroy_timer(obj->timer);
    }
    if (obj->event_queue) {
        al_destroy_event_queue(obj->event_queue);
    }
    free(obj);
    free(self);
}