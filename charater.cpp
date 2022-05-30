#include "charater.h"

// the state of character
enum {STOP = 0, MOVE, ATK};



/*
typedef struct character
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[2];
    ALLEGRO_BITMAP *img_atk[2];
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
}Character;

Character chara;
*/

ALLEGRO_SAMPLE *sample = NULL;

float CameraPosition[ 2 ] = { 0.0, 0.0 };
ALLEGRO_TRANSFORM camera;
Character *pCharacter;

void CameraUpdate( float *CamPosition, int x, int y, int width, int height )
{
    //CamPosition[ 0 ] = -( WIDTH / 2 ) + ( x + width / 2 );
    //CamPosition[ 1 ] = -( HEIGHT / 2 ) + ( y + height / 2 );
    CamPosition[ 0 ] = -( WIDTH / 2 ) + ( x );
    CamPosition[ 1 ] = -( HEIGHT / 2 ) + ( y );

    if( CamPosition[ 0 ] < 0 ) {
        CamPosition[ 0 ] = 0.0;
    }
    else if( CamPosition[ 0 ] >= 500 ) {
        CamPosition[ 0 ] = 500.0;
    }

    CamPosition[ 1 ] = 0;
}

void character_init(){
    // load character images
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/char_move%d.png", i );
        pchara->img_move[i-1] = al_load_bitmap(temp);
    }
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/char_atk%d.png", i );
        pchara->img_atk[i-1] = al_load_bitmap(temp);
    }
    // load effective sound
    sample = al_load_sample("./sound/atk_sound.wav");
    pchara->atk_Sound  = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pchara->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pchara->atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    pchara->width = al_get_bitmap_width(pchara->img_move[0]);
    pchara->height = al_get_bitmap_height(pchara->img_move[0]);
    pchara->x = WIDTH/2;
    pchara->y = HEIGHT/2;
    pchara->dir = false;

    // initial the animation component
    pchara->state = STOP;
    pchara->anime = 0;
    pchara->anime_time = 30;
}

void charater_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            pchara->anime++;
            pchara->anime %= pchara->anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        pchara->anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}

void charater_update(){
    // use the idea of finite state machine to deal with different state
    if( key_state[ALLEGRO_KEY_W] ){
        pchara->y -= 5;
        pchara->state = MOVE;
    }else if( key_state[ALLEGRO_KEY_A] ){
        pchara->dir = false;
        pchara->x -= 5;
        pchara->state = MOVE;
    }else if( key_state[ALLEGRO_KEY_S] ){
        pchara->y += 5;
        pchara->state = MOVE;
    }else if( key_state[ALLEGRO_KEY_D] ){
        pchara->dir = true;
        pchara->x += 5;
        pchara->state = MOVE;
    }else if( key_state[ALLEGRO_KEY_SPACE] ){
        pchara->state = ATK;
    }else if( pchara->anime == pchara->anime_time-1 ){
        pchara->anime = 0;
        pchara->state = STOP;
    }else if ( pchara->anime == 0 ){
        pchara->state = STOP;
    }
}
void character_draw(){

    CameraUpdate( CameraPosition, pchara->x, pchara->y, pchara->width, pchara->height );
    al_identity_transform( &camera );
    al_translate_transform( &camera, -CameraPosition[ 0 ], -CameraPosition[ 1 ] );
    al_use_transform( &camera );

    // with the state, draw corresponding image
    if( pchara->state == STOP ){
        if( pchara->dir )
            al_draw_bitmap(pchara->img_move[0], pchara->x, pchara->y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(pchara->img_move[0], pchara->x, pchara->y, 0);
    }else if( pchara->state == MOVE ){
        if( pchara->dir ){
            if( pchara->anime < pchara->anime_time/2 ){
                al_draw_bitmap(pchara->img_move[0], pchara->x, pchara->y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(pchara->img_move[1], pchara->x, pchara->y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }else{
            if( pchara->anime < pchara->anime_time/2 ){
                al_draw_bitmap(pchara->img_move[0], pchara->x, pchara->y, 0);
            }else{
                al_draw_bitmap(pchara->img_move[1], pchara->x, pchara->y, 0);
            }
        }
    }else if( pchara->state == ATK ){
        if( pchara->dir ){
            if( pchara->anime < pchara->anime_time/2 ){
                al_draw_bitmap(pchara->img_atk[0], pchara->x, pchara->y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(pchara->img_atk[1], pchara->x, pchara->y, ALLEGRO_FLIP_HORIZONTAL);
                al_play_sample_instance(pchara->atk_Sound);
            }
        }else{
            if( pchara->anime < pchara->anime_time/2 ){
                al_draw_bitmap(pchara->img_atk[0], pchara->x, pchara->y, 0);
            }else{
                al_draw_bitmap(pchara->img_atk[1], pchara->x, pchara->y, 0);
                al_play_sample_instance(pchara->atk_Sound);
            }
        }
    }
}
void character_destory(){
    al_destroy_bitmap(pchara->img_atk[0]);
    al_destroy_bitmap(pchara->img_atk[1]);
    al_destroy_bitmap(pchara->img_move[0]);
    al_destroy_bitmap(pchara->img_move[1]);
    al_destroy_sample_instance(pchara->atk_Sound);
}
