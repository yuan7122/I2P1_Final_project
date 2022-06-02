#include "charater.h"

// the state of character
enum {STOP = 0, MOVE, ATK};

ALLEGRO_SAMPLE *sample = NULL;

float g_CameraPosition[ 2 ] = { 0.0, 0.0 };
ALLEGRO_TRANSFORM camera;
Character *pCharacter;

float g_Gravity = 9.8;
float g_Tick = 0.3;
int g_nTerrainWidth = 0;

void CameraUpdate( float *CamPosition, int x, int y, int width, int height )
{
    //CamPosition[ 0 ] = -( WIDTH / 2 ) + ( x + width / 2 );
    //CamPosition[ 1 ] = -( HEIGHT / 2 ) + ( y + height / 2 );
    CamPosition[ 0 ] = -( WIDTH / 2 ) + ( x );
    CamPosition[ 1 ] = -( HEIGHT / 2 ) + ( y );

    if( CamPosition[ 0 ] < 0 ) {
        CamPosition[ 0 ] = 0.0;
    }
    else if( CamPosition[ 0 ] >= g_nTerrainWidth ) {
        CamPosition[ 0 ] = ( float )g_nTerrainWidth;
    }

    CamPosition[ 1 ] = 0;
}

void character_init( const int nTerrainWidth ){
    // load character images
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/char_move_small%d.png", i );
        e_pchara->img_move[i-1] = al_load_bitmap(temp);
    }
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/char_atk_small%d.png", i );
        e_pchara->img_atk[i-1] = al_load_bitmap(temp);
    }
    // load effective sound
    sample = al_load_sample("./sound/atk_sound.wav");
    e_pchara->atk_Sound  = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(e_pchara->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(e_pchara->atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    e_pchara->width = al_get_bitmap_width(e_pchara->img_move[0]);
    e_pchara->height = al_get_bitmap_height(e_pchara->img_move[0]);
    e_pchara->x = WIDTH/2;
    e_pchara->y = HEIGHT/2;
    e_pchara->dir = false;

    // initial the animation component
    e_pchara->state = STOP;
    e_pchara->anime = 0;
    e_pchara->anime_time = 30;

    // gravity
    e_pchara->y0 = e_pchara->y;
    e_pchara->vy = 0.0;
    e_pchara->FallingTick = 0.0;

    // terrain width
    g_nTerrainWidth = nTerrainWidth;
}

void charater_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            e_pchara->anime++;
            e_pchara->anime %= e_pchara->anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        e_pchara->anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}

void charater_update(){
    // use the idea of finite state machine to deal with different state
    if( key_state[ALLEGRO_KEY_W] ){
        e_pchara->vy = -70; // jump upward velocity
        // ToDo:
        // 1. prevent second jump before certain time of the first jump
        // 2. only two consecutive jump is allowed

        e_pchara->state = MOVE;
    }else if( key_state[ALLEGRO_KEY_A] ){
        e_pchara->dir = false;
        e_pchara->x -= 10;
        e_pchara->state = MOVE;
    }else if( key_state[ALLEGRO_KEY_S] ){
        e_pchara->y += 10;
        e_pchara->state = MOVE;
    }else if( key_state[ALLEGRO_KEY_D] ){
        e_pchara->dir = true;
        e_pchara->x += 10;
        e_pchara->state = MOVE;
    }else if( key_state[ALLEGRO_KEY_SPACE] ){
        e_pchara->state = ATK;
    }else if( e_pchara->anime == e_pchara->anime_time-1 ){
        e_pchara->anime = 0;
        e_pchara->state = STOP;
    }else if ( e_pchara->anime == 0 ){
        e_pchara->state = STOP;
    }
}

void character_gravity( const int nGroundY ) {
    if( nGroundY == -1 ) {
        return;
    }

    // ticktock
    e_pchara->FallingTick += g_Tick;

    // velocity;
    e_pchara->vy += g_Gravity * g_Tick;
    // position
    e_pchara->y = e_pchara->y0
        + ( int )(e_pchara->vy * e_pchara->FallingTick + ( 0.5 * g_Gravity * ( e_pchara->FallingTick * e_pchara->FallingTick ) ) );


    if( ( e_pchara->y + e_pchara->height ) >= nGroundY ) {
        e_pchara->y = nGroundY - e_pchara->height;
        e_pchara->y0 = e_pchara->y;
        e_pchara->vy = 0.0;
        e_pchara->FallingTick = 0;
    }
    else {
        // do nothing
    }
}

void character_draw( const int nGroundY ){

    CameraUpdate( g_CameraPosition, e_pchara->x, e_pchara->y, e_pchara->width, e_pchara->height );
    al_identity_transform( &camera );
    al_translate_transform( &camera, -g_CameraPosition[ 0 ], -g_CameraPosition[ 1 ] );
    al_use_transform( &camera );

    character_gravity( nGroundY );

    // with the state, draw corresponding image
    if( e_pchara->state == STOP ){
        if( e_pchara->dir )
            al_draw_bitmap(e_pchara->img_move[0], e_pchara->x, e_pchara->y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(e_pchara->img_move[0], e_pchara->x, e_pchara->y, 0);
    }else if( e_pchara->state == MOVE ){
        if( e_pchara->dir ){
            if( e_pchara->anime < e_pchara->anime_time/2 ){
                al_draw_bitmap(e_pchara->img_move[0], e_pchara->x, e_pchara->y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(e_pchara->img_move[1], e_pchara->x, e_pchara->y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }else{
            if( e_pchara->anime < e_pchara->anime_time/2 ){
                al_draw_bitmap(e_pchara->img_move[0], e_pchara->x, e_pchara->y, 0);
            }else{
                al_draw_bitmap(e_pchara->img_move[1], e_pchara->x, e_pchara->y, 0);
            }
        }
    }else if( e_pchara->state == ATK ){
        if( e_pchara->dir ){
            if( e_pchara->anime < e_pchara->anime_time/2 ){
                al_draw_bitmap(e_pchara->img_atk[0], e_pchara->x, e_pchara->y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(e_pchara->img_atk[1], e_pchara->x, e_pchara->y, ALLEGRO_FLIP_HORIZONTAL);
                al_play_sample_instance(e_pchara->atk_Sound);
            }
        }else{
            if( e_pchara->anime < e_pchara->anime_time/2 ){
                al_draw_bitmap(e_pchara->img_atk[0], e_pchara->x, e_pchara->y, 0);
            }else{
                al_draw_bitmap(e_pchara->img_atk[1], e_pchara->x, e_pchara->y, 0);
                al_play_sample_instance(e_pchara->atk_Sound);
            }
        }
    }
}
void character_destory(){
    al_destroy_bitmap(e_pchara->img_atk[0]);
    al_destroy_bitmap(e_pchara->img_atk[1]);
    al_destroy_bitmap(e_pchara->img_move[0]);
    al_destroy_bitmap(e_pchara->img_move[1]);
    al_destroy_sample_instance(e_pchara->atk_Sound);
}
