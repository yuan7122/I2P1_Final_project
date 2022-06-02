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
        pchara->img_move[i-1] = al_load_bitmap(temp);
    }
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/char_atk_small%d.png", i );
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

    // gravity
    pchara->y0 = pchara->y;
    pchara->vy = 0.0;
    pchara->FallingTick = 0.0;

    // terrain width
    g_nTerrainWidth = nTerrainWidth;
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
        pchara->vy = -70; // jump upward velocity
        // ToDo:
        // 1. prevent second jump before certain time of the first jump
        // 2. only two consecutive jump is allowed

        pchara->state = MOVE;
    }else if( key_state[ALLEGRO_KEY_A] ){
        pchara->dir = false;
        pchara->x -= 10;
        pchara->state = MOVE;
    }else if( key_state[ALLEGRO_KEY_S] ){
        pchara->y += 10;
        pchara->state = MOVE;
    }else if( key_state[ALLEGRO_KEY_D] ){
        pchara->dir = true;
        pchara->x += 10;
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

void character_gravity( const int nGroundY ) {
    if( nGroundY == -1 ) {
        return;
    }

    // ticktock
    pchara->FallingTick += g_Tick;

    // velocity;
    pchara->vy += g_Gravity * g_Tick;
    // position
    pchara->y = pchara->y0
        + ( int )(pchara->vy * pchara->FallingTick + ( 0.5 * g_Gravity * ( pchara->FallingTick * pchara->FallingTick ) ) );


    if( ( pchara->y + pchara->height ) >= nGroundY ) {
        pchara->y = nGroundY - pchara->height;
        pchara->y0 = pchara->y;
        pchara->vy = 0.0;
        pchara->FallingTick = 0;
    }
    else {
        // do nothing
    }
}

void character_draw( const int nGroundY ){

    CameraUpdate( g_CameraPosition, pchara->x, pchara->y, pchara->width, pchara->height );
    al_identity_transform( &camera );
    al_translate_transform( &camera, -g_CameraPosition[ 0 ], -g_CameraPosition[ 1 ] );
    al_use_transform( &camera );

    character_gravity( nGroundY );

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
