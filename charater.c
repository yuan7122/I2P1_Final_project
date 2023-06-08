#include "charater.h"
/*
   [Character function]
*/
Elements* New_Character(int label)
{
    Character* pDerivedObj = (Character*)malloc(sizeof(Character));
    Elements* pObj = New_Elements(label);
    // setting derived object member
    // load character images
    for(int i = 1 ; i <= 2 ; i++)
    {
        char temp[50];
        sprintf( temp, "./image/char_move%d.png", i );
        pDerivedObj->img_move[i-1] = al_load_bitmap(temp);
    }
    for(int i = 1 ; i <= 2 ; i++)
    {
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
    pDerivedObj->x = 300;
    pDerivedObj->y = HEIGHT - pDerivedObj->height - 60;
    pDerivedObj->dir = false; // true: face to right, false: face to left

    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->anime = 0;
    pDerivedObj->anime_time = 30;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Process = Character_process;
    pObj->Draw = Character_draw;
    pObj->Update = Character_update;
    pObj->Interact = Character_interact;
    pObj->Destroy = Character_destory;
    return pObj;
}


void Character_process(Elements* const ele, ALLEGRO_EVENT event)
{
    Character *chara = ((Character*)(ele->pDerivedObj));
    // process the keyboard event
    if( event.type == ALLEGRO_EVENT_KEY_DOWN )
    {
        key_state[event.keyboard.keycode] = true;
    }
    else if( event.type == ALLEGRO_EVENT_KEY_UP )
    {
        key_state[event.keyboard.keycode] = false;
    }
}
void Character_update(Elements* const ele)
{
    // use the idea of finite state machine to deal with different state
    Character *chara = ((Character*)(ele->pDerivedObj));
    if(chara->state == STOP)
    {
        if( key_state[ALLEGRO_KEY_SPACE] )
        {
            chara->anime = 1;
            chara->state = ATK;
        }
        else if( key_state[ALLEGRO_KEY_A] )
        {
            chara->anime = 1;
            chara->dir = false;
            chara->state = MOVE;
        }
        else if( key_state[ALLEGRO_KEY_D] )
        {
            chara->anime = 1;
            chara->dir = true;
            chara->state = MOVE;
        }
        else
        {
            chara->state = STOP;
        }
    }
    else if(chara->state == MOVE)
    {
        if( key_state[ALLEGRO_KEY_SPACE] )
        {
            chara->anime = 1;
            chara->state = ATK;
        }
        else if( key_state[ALLEGRO_KEY_A] )
        {
            chara->dir = false;
            chara->x -= 5;
            chara->state = MOVE;
        }
        else if( key_state[ALLEGRO_KEY_D] )
        {
            chara->dir = true;
            chara->x += 5;
            chara->state = MOVE;
        }else if( chara->anime >= chara->anime_time ) chara->state = STOP;
    }
    else if(chara->state == ATK)
    {
        if(chara->anime >= chara->anime_time) chara->state = STOP;
    }
    // process anime time
    if( chara->anime > 0 && chara->anime < chara->anime_time )
    {
        chara->anime++;
    }
    else
    {
        if(chara->state == MOVE) chara->anime = 1;
        else chara->anime = 0;
    }
}
void Character_interact(Elements* const self_ele, Elements* const ele) {}
void Character_draw(Elements* const ele)
{
    // with the state, draw corresponding image
    Character *chara = ((Character*)(ele->pDerivedObj));
    if( chara->state == STOP )
    {

        if( chara->dir )
            al_draw_bitmap(chara->img_move[0], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(chara->img_move[0], chara->x, chara->y, 0);
    }
    else if( chara->state == MOVE )
    {
        if( chara->dir )
        {
            if( chara->anime < chara->anime_time/2 )
            {
                al_draw_bitmap(chara->img_move[0], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else
            {
                al_draw_bitmap(chara->img_move[1], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }
        else
        {
            if( chara->anime < chara->anime_time/2 )
            {
                al_draw_bitmap(chara->img_move[0], chara->x, chara->y, 0);
            }
            else
            {
                al_draw_bitmap(chara->img_move[1], chara->x, chara->y, 0);
            }
        }
    }
    else if( chara->state == ATK )
    {
        if( chara->dir )
        {
            if( chara->anime < chara->anime_time/2 )
            {
                al_draw_bitmap(chara->img_atk[0], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
                chara->new_proj = false;
            }
            else
            {
                al_draw_bitmap(chara->img_atk[1], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
                al_play_sample_instance(chara->atk_Sound);
                if(!chara->new_proj)
                {
                    Elements* pro = New_Projectile(Projectile_L + scene->ele_len,
                                                   chara->x + chara->width - 100,
                                                   chara->y + 10,
                                                   5 );
                    _Register_elements(scene, pro);
                    chara->new_proj = true;
                }

            }
        }
        else
        {
            if( chara->anime < chara->anime_time/2 )
            {
                al_draw_bitmap(chara->img_atk[0], chara->x, chara->y, 0);
                chara->new_proj = false;
            }
            else
            {
                al_draw_bitmap(chara->img_atk[1], chara->x, chara->y, 0);
                al_play_sample_instance(chara->atk_Sound);
                if(!chara->new_proj)
                {
                    Elements* pro = New_Projectile(Projectile_L + scene->ele_len,
                                                   chara->x - 50,
                                                   chara->y + 10,
                                                   -5 );
                    _Register_elements(scene, pro);
                    chara->new_proj = true;
                }
            }
        }
    }
}
void Character_destory(Elements* const ele)
{
    Character *chara = ((Character*)(ele->pDerivedObj));
    al_destroy_bitmap(chara->img_atk[0]);
    al_destroy_bitmap(chara->img_atk[1]);
    al_destroy_bitmap(chara->img_move[0]);
    al_destroy_bitmap(chara->img_move[1]);
    al_destroy_sample_instance(chara->atk_Sound);
}
