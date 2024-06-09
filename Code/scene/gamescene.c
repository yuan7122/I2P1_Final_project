#include "gamescene.h"
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
/*
   [GameScene function]
*/
#define DAY_DURATION 60   // 白天持續時間（秒）
#define DUSK1_DURATION 40 // 黃昏一持續時間（秒）
#define DUSK2_DURATION 20 // 黃昏二持續時間（秒）
#define NIGHT_DURATION 10 // 黑夜持續時間（秒）

// 定義背景狀態
enum BackgroundState {
    DAY,
    DUSK1,
    DUSK2,
    NIGHT
};

// 全局變量
enum BackgroundState background_state = DAY;
int elapsed_time = 0;
ALLEGRO_TIMER *timer = NULL;

// 切換背景函數
void switch_background() {
    switch (background_state) {
        case DAY:
            background_state = DUSK1;
            printf("Change from 'DAY' to 'DUSK1'");
            break;
        case DUSK1:
            background_state = DUSK2;
            printf("Change from 'DUSK1' to 'DUSK2'");
            break;
        case DUSK2:
            background_state = NIGHT;
            printf("Change from 'DUSK2' to 'NIGHT'");
            break;
        case NIGHT:
            background_state = DAY;
            printf("Change from 'NIGHT' to 'DAY'");
            break;
        default:
            break;
    }
}

Scene *New_GameScene(int label)
{
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->day_background = al_load_bitmap("assets/image/day.jpeg");
    pDerivedObj->dusk1_background = al_load_bitmap("assets/image/dusk1.jpeg");
    pDerivedObj->dusk2_background = al_load_bitmap("assets/image/dusk2.jpeg");
    pDerivedObj->night_background = al_load_bitmap("assets/image/night.jpeg");
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 30, 0);
    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_Floor(Floor_L));
    _Register_elements(pObj, New_Teleport(Teleport_L));
    _Register_elements(pObj, New_Tree(Tree_L));
    _Register_elements(pObj, New_Character(Character_L));
    // setting derived object function
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    // 初始化事件队列和定时器
    timer = al_create_timer(1.0);
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    return pObj;
}
void game_scene_update(Scene *self)
{
    /*
    // update every element
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {

        allEle.arr[i]->Update(allEle.arr[i]);
    }

    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++)
        {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int i = 0; i < labelEle.len; i++)
            {
                ele->Interact(ele, labelEle.arr[i]);
            }
        }
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }*/

   ALLEGRO_EVENT ev;
    while (al_get_next_event(event_queue, &ev)) {
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            elapsed_time++;
            int current_duration = 0;
            switch (background_state) {
                case DAY:
                    current_duration = DAY_DURATION;
                    break;
                case DUSK1:
                    current_duration = DUSK1_DURATION;
                    break;
                case DUSK2:
                    current_duration = DUSK2_DURATION;
                    break;
                case NIGHT:
                    current_duration = NIGHT_DURATION;
                    break;
            }
            if (elapsed_time >= current_duration) {
                switch_background();
                elapsed_time = 0;
            }
        }
    }
    // 更新所有元素
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++) {
        allEle.arr[i]->Update(allEle.arr[i]);
    }

    // 互動檢查
    for (int i = 0; i < allEle.len; i++) {
        Elements *ele = allEle.arr[i];
        for (int j = 0; j < ele->inter_len; j++) {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int i = 0; i < labelEle.len; i++) {
                ele->Interact(ele, labelEle.arr[i]);
            }
        }
    }

    // 移除需要刪除的元素
    for (int i = 0; i < allEle.len; i++) {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }
}
void game_scene_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = NULL;

    /*al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
    char score_text[50];
    sprintf(score_text, "Total Score: %d", tot_score);
    al_draw_text(gs->font, al_map_rgb(0, 0, 0), 790, 60, 50, score_text);*/
    switch (background_state) {
        case DAY:
            background = gs->day_background;
            break;
        case DUSK1:
            background = gs->dusk1_background;
            break;
        case DUSK2:
            background = gs->dusk2_background;
            break;
        case NIGHT:
            background = gs->night_background;
            break;
    }
    if (background != NULL) {
        al_draw_bitmap(background, 0, 0, 0);
    }

    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++) {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
    char score_text[50];
    sprintf(score_text, "Total Score: %d", tot_score);
    al_draw_text(gs->font, al_map_rgb(0, 0, 0), 790, 60, 50, score_text);
}
void game_scene_destroy(Scene *self)
{
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->day_background);
    al_destroy_bitmap(Obj->dusk1_background);
    al_destroy_bitmap(Obj->dusk2_background);
    al_destroy_bitmap(Obj->night_background);
    al_destroy_font(Obj->font);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    al_destroy_timer(timer);
    free(Obj);
    free(self);
}
