#include "menu.h"
/*
   [Menu function]
*/
Scene* New_Menu(int label)
{
    Menu* pDerivedObj = (Menu*)malloc(sizeof(Menu));
    Scene* pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("./font/pirulen.ttf",12,0);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Process = menu_process;
    pObj->Update = menu_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    return pObj;
}
void menu_process(Scene* const pMenuObj, ALLEGRO_EVENT event)
{
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
        {
            pMenuObj->scene_end = true;
            window = 1;
        }
}
void menu_update(Scene* const pMenuObj)
{
    return;
}
void menu_draw(Scene* const pMenuObj)
{
    al_clear_to_color(al_map_rgb(100,100,100));
    Menu* Obj = ((Menu*)(pMenuObj->pDerivedObj));
    al_draw_text(Obj->font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+220, ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    al_draw_rectangle(WIDTH/2-150, 510, WIDTH/2+150, 550, al_map_rgb(255, 255, 255), 0);
}
void menu_destroy(Scene* const pMenuObj)
{
    Menu* Obj = ((Menu*)(pMenuObj->pDerivedObj));
    al_destroy_font(Obj->font);
}
