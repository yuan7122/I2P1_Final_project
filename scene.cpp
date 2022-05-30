#include "scene.h"

ALLEGRO_FONT *font = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *background2[ 10 ] = { NULL };
int g_nWidth = 0;
int g_nHeight = 0;

// function of menu
void menu_init(){
    font = al_load_ttf_font("./font/pirulen.ttf",12,0);
}
void menu_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = true;
}
void menu_draw(){
    al_clear_to_color(al_map_rgb(100,100,100));
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+220 , ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    al_draw_rectangle(WIDTH/2-150, 510, WIDTH/2+150, 550, al_map_rgb(255, 255, 255), 0);
}
void menu_destroy(){
    al_destroy_font(font);
}

// function of game_scene
void game_scene_init(){
    character_init();
    background = al_load_bitmap("./image/stage.jpg");
    for( int i = 0; i < 10; i++ ) {
        background2[ i ] = al_load_bitmap("./image/stage.jpg");
    }

    //background = al_load_bitmap("./image/20220528211610.png");
    g_nWidth = al_get_bitmap_width( background );
    g_nHeight = al_get_bitmap_height( background );
}

void game_scene_draw(){
    //al_draw_bitmap(background, 0, 0, 0);

    for( int i = 0; i < 10; i++ ) {
       al_draw_bitmap( background2[ i ], i * g_nWidth, 0, 0 );
    }

    // ¦aªO
    // ...
    character_draw();
}

/*
0         255|256          511|          |          |
  v  ++++++                       +++
++++++                    +++
                v      ++
         ++++++++++++++
 */

void game_scene_destroy(){
    al_destroy_bitmap(background);
    character_destory();
}
