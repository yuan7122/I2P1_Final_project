#include "charater.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
#include "seeds_c.h"
/*
   [Character function]
*/
Elements *New_Character(int label)
{
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load character images
    char state_string[5][10] = {"farmer", "farmer", "farmer", "farmer", "farmer"};
    //pDerivedObj->img = al_load_bitmap("assets/image/farmer.png");
    //pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    //pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    //char state_string[3][10] = {"stop", "move", "attack"};
    for (int i = 0; i < 5; i++)
    {
        char buffer[60];
        sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    /*for (int i = 0; i < 5; i++)
    {
        char buffer[60];
        sprintf(buffer, "assets/image/farmer.jpg");
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    */
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    //initial the geometric information of character
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 300;
    pDerivedObj->y = HEIGHT - pDerivedObj->height ;//- 60;
    printf("h:%d objecth:%d\n", HEIGHT, pDerivedObj->height);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    //printf("character hitbox:%d\n", pDerivedObj->hitbox);
    pDerivedObj->dir = false; // true: face two right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Character_draw;
    pObj->Update = Character_update;
    pObj->Interact = Character_interact;
    pObj->Destroy = Character_destory;
    return pObj;
}
void Character_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    Character *chara = ((Character *)(self->pDerivedObj));
    //printf("Character state: %d\n", chara->state);
    if (chara->state == STOP)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_W]) // Handle jump mode
        {
            chara->state = JUMP;
            chara->jump_speed = 10; // Set initial jump speed
        }
        else if (key_state[ALLEGRO_KEY_S]) // Handle jump mode
        {
            chara->state = DOWN;
            chara->jump_speed = -10; // Set initial jump speed
        }
        else if (key_state[ALLEGRO_KEY_2])
        {
            Elements *pro;
            printf("ALLEGRO_KEY_2 pressed\n");
            pro = New_Seeds_c(Seeds_c_L, chara->x-30+chara->width/2, chara->y);
            printf("chara->x = %d, chara->y = %d", chara->x, chara->y);
            printf("now scene has %d objects\n",scene->ele_num);
            printf("after newseeds\n");
            _Register_elements(scene, pro);
            if (!pro) {
                fprintf(stderr, "Failed to create new Seeds_c\n");
            } else {
                _Register_elements(scene, pro);
                printf("New seed created and registered\n");
            }
            //chara->new_proj = true;
            chara->state = MOVE;
        }
        /* else if (key_state[ALLEGRO_KEY_F])
        {
            // Handle watering seeds when F key is pressed
            printf("ALLEGRO_KEY_F pressed\n");
            Scene *currentScene = scene;  // 获取当前场景
            if (currentScene != NULL)
            {
                
                ElementVec allSeeds = _Get_label_elements(currentScene, Seeds_c_L);
                for (int i = 0; i < allSeeds.len; i++)
                {
                    Elements *seedElement = allSeeds.arr[i];
                    Seeds_c *seed = (Seeds_c *)(seedElement->pDerivedObj);
                    printf("Seeds id = %d\n", seedElement->id);
                    // 检查角色和种子之间的距离
                    int distance_x = abs(chara->x - seed->x);
                    int distance_y = abs(chara->y - seed->y);
                    int max_distance = 50; // 设置一个距离阈值

                    if (distance_x <= max_distance && distance_y <= max_distance)
                    {
                        water_seeds_c(seedElement); // 为附近的种子浇水
                    }
                }
            }
        }*/
        else
        {
            chara->state = STOP;
        }
    }
    else if (chara->state == MOVE)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            _Character_update_position(self, -5, 0);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            _Character_update_position(self, 5, 0);
            chara->state = MOVE;
        }
        if (chara->gif_status[chara->state]->done)
            chara->state = STOP;
    }
    else if (chara->state == ATK)
    {
        if (chara->gif_status[chara->state]->done)
        {
            chara->state = STOP;
            chara->new_proj = false;
        }
        if (chara->gif_status[ATK]->display_index == 2 && chara->new_proj == false)
        {
            Elements *pro;
            if (chara->dir)
            {
                pro = New_Projectile(Projectile_L,
                                     chara->x + chara->width - 100,
                                     chara->y + 10,
                                     5);
            }
            else
            {
                pro = New_Projectile(Projectile_L,
                                     chara->x - 50,
                                     chara->y + 10,
                                     -5);
            }
            _Register_elements(scene, pro);
            chara->new_proj = true;
        }
    }
    else if (chara->state == JUMP) // Handle jump mode
    {
        int GRAVITY = -10;
        //int GROUND_LEVEL = 0;
        _Character_update_position(self, 0, chara->jump_speed);
        chara->jump_speed += GRAVITY; // Apply gravity
        if (chara->y <= 0) // Check if landed
        {
            chara->y = 0; // Reset position
            chara->jump_speed = 0;
            chara->state = STOP; // Return to STOP state after landing
        }
        if (chara->y >= HEIGHT) // Check if landed
        {
            chara->y = HEIGHT; // Reset position
            chara->jump_speed = 0;
            chara->state = STOP; // Return to STOP state after landing
        }
    }
    else if (chara->state == DOWN) // Handle crouch mode
    {
        int GRAVITY = 10;
        //int GROUND_LEVEL = 0;
        _Character_update_position(self, 0, chara->jump_speed);
        chara->jump_speed += GRAVITY; // Apply gravity - Gravity not applied in crouch mode
        //if (chara->y <= 5) // Check if landed
        //{
            //chara->y = 5; // Reset position
            //chara->jump_speed = 0;
            //chara->state = STOP; // Return to STOP state after landing
        //}
        if (chara->y >= HEIGHT-160) // Check if landed
        {
            chara->y = HEIGHT-160; // Reset position
            chara->jump_speed = 0;
            chara->state = STOP; // Return to STOP state after landing
        }
    }
}
void Character_draw(Elements *self)
{
    // with the state, draw corresponding image
    Character *chara = ((Character *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
    }
    if (chara->state == ATK && chara->gif_status[chara->state]->display_index == 2)
    {
        al_play_sample_instance(chara->atk_Sound);
    }
}
void Character_destory(Elements *self)
{
    Character *Obj = ((Character *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 5; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Character_update_position(Elements *self, int dx, int dy)
{
    Character *chara = ((Character *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Character_interact(Elements *self, Elements *tar) {}
