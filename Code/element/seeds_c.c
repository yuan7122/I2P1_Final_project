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
    pDerivedObj->timer = al_create_timer(1.0);
    pDerivedObj->countdown = 50;
    pDerivedObj->event_queue = al_create_event_queue();
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

            if (elapsed_time >= 50.0) {
                Obj->is_harvestable = true;
            }
            if (Obj->countdown > 0) {
                Obj->countdown = 50 - (int)elapsed_time;
                if (Obj->countdown <= 0) {
                    Obj->countdown = 0;
                    Obj->is_harvestable = true;
                }
            }
        }
    }
}
void Seeds_c_interact(Elements *self, Elements *tar)
{
    /*Seeds_c *Obj = ((Seeds_c *)(self->pDerivedObj));
    if (tar->label == Character_L && Obj->is_harvestable) {
        Obj->score += 5; // 收成後增加積分
        Obj->is_harvestable = false; // 重置為不可收成狀態
        Obj->plant_time = al_get_time(); // 重置種植時間
        Obj->countdown = 50; // 重置倒數時間
        al_start_timer(Obj->timer); // 重啟計時器
    }*/
   // 这里假设 Character 使用的是 'Character' 标签
    Seeds_c *Obj = ((Seeds_c *)(self->pDerivedObj));
    //printf("in seeds_c interact\n");
    if (tar->label == Character_L&&Obj->is_harvestable&&key_state[ALLEGRO_KEY_H]) {
        Seeds_c *Obj = (Seeds_c *)(self->pDerivedObj);
        Character *chara = (Character *)(tar->pDerivedObj);
        if (chara->hitbox->overlap(chara->hitbox, Obj->hitbox))
        {
            self->dele = true;
            //printf("-10s\n"); // 打印 -10s
        }
        // 检查是否碰撞
        else {
            //printf("No collision detected\n"); // 没有检测到碰撞
        }
    }
}
// 修改 Seeds_c 的繪製函數
void Seeds_c_draw(Elements *self) 
{
    Seeds_c *Obj = ((Seeds_c *)(self->pDerivedObj));
    if (Obj->is_harvestable) {
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(255, 255, 255), Obj->x, Obj->y, 0);
    } else {
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(128, 128, 128), Obj->x, Obj->y, 0);
    }
    ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);
    al_draw_textf(Obj->font, text_color, Obj->x + Obj->width / 2, Obj->y + Obj->height, ALLEGRO_ALIGN_CENTER, "Score: %d", Obj->score);
    al_draw_textf(Obj->font, text_color, Obj->x + Obj->width / 2, Obj->y - 20, ALLEGRO_ALIGN_CENTER, "Time: %d", Obj->countdown);
}

void Seeds_c_destory(Elements *self) 
{
    Seeds_c *obj = (Seeds_c *)(self->pDerivedObj);
    al_destroy_bitmap(obj->img);
    free(obj->hitbox);
    al_destroy_font(obj->font);
    al_destroy_timer(obj->timer);
    al_destroy_event_queue(obj->event_queue);
    free(obj);
    free(self);
}