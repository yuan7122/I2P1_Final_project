#include "charater.h"
/*
   [Character function]
*/
Elements* New_Character(char* label){
    Character* pDerivedObj = (Character*)malloc(sizeof(Character));
    Elements* pObj = New_Elements(label);
    // setting derived object member
    // load character images
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/char_move%d.png", i );
        pDerivedObj->img_move[i-1] = al_load_bitmap(temp);
    }
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/char_atk%d.png", i );
        pDerivedObj->img_atk[i-1] = al_load_bitmap(temp);
    }
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("./sound/atk_sound.wav");
    pDerivedObj->atk_Sound  = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img_move[0]);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img_move[0]);
    pDerivedObj->x = WIDTH/2;
    pDerivedObj->y = HEIGHT/2;
    pDerivedObj->dir = false;

    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->anime = 0;
    pDerivedObj->anime_time = 30;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Process = charater_process;
    pObj->Draw = character_draw;
    pObj->Update = charater_update;
    pObj->Destroy = character_destory;
    return pObj;
}


void charater_process(Elements* const ele, ALLEGRO_EVENT event){
    Character *chara = ((Character*)(ele->pDerivedObj));
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara->anime++;
            chara->anime %= chara->anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        chara->anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}
void charater_update(Elements* const ele){
    // use the idea of finite state machine to deal with different state
    Character *chara = ((Character*)(ele->pDerivedObj));
    if( key_state[ALLEGRO_KEY_W] ){
        chara->y -= 5;
        chara->state = MOVE;
    }else if( key_state[ALLEGRO_KEY_A] ){
        chara->dir = false;
        chara->x -= 5;
        chara->state = MOVE;
    }else if( key_state[ALLEGRO_KEY_S] ){
        chara->y += 5;
        chara->state = MOVE;
    }else if( key_state[ALLEGRO_KEY_D] ){
        chara->dir = true;
        chara->x += 5;
        chara->state = MOVE;
    }else if( key_state[ALLEGRO_KEY_SPACE] ){
        chara->state = ATK;
    }else if( chara->anime == chara->anime_time-1 ){
        chara->anime = 0;
        chara->state = STOP;
    }else if ( chara->anime == 0 ){
        chara->state = STOP;
    }
}
void character_draw(Elements* const ele){
    // with the state, draw corresponding image
    Character *chara = ((Character*)(ele->pDerivedObj));
    if( chara->state == STOP ){
        if( chara->dir )
            al_draw_bitmap(chara->img_move[0], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(chara->img_move[0], chara->x, chara->y, 0);
    }else if( chara->state == MOVE ){
        if( chara->dir ){
            if( chara->anime < chara->anime_time/2 ){
                al_draw_bitmap(chara->img_move[0], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara->img_move[1], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }else{
            if( chara->anime < chara->anime_time/2 ){
                al_draw_bitmap(chara->img_move[0], chara->x, chara->y, 0);
            }else{
                al_draw_bitmap(chara->img_move[1], chara->x, chara->y, 0);
            }
        }
    }else if( chara->state == ATK ){
        if( chara->dir ){
            if( chara->anime < chara->anime_time/2 ){
                al_draw_bitmap(chara->img_atk[0], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara->img_atk[1], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
                al_play_sample_instance(chara->atk_Sound);
            }
        }else{
            if( chara->anime < chara->anime_time/2 ){
                al_draw_bitmap(chara->img_atk[0], chara->x, chara->y, 0);
            }else{
                al_draw_bitmap(chara->img_atk[1], chara->x, chara->y, 0);
                al_play_sample_instance(chara->atk_Sound);
            }
        }
    }
}
void character_destory(Elements* const ele){
    Character *chara = ((Character*)(ele->pDerivedObj));
    al_destroy_bitmap(chara->img_atk[0]);
    al_destroy_bitmap(chara->img_atk[1]);
    al_destroy_bitmap(chara->img_move[0]);
    al_destroy_bitmap(chara->img_move[1]);
    al_destroy_sample_instance(chara->atk_Sound);
}
