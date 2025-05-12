#include "GameWindow.h"
#include "GAME_ASSERT.h"
#include "global.h"
#include "shapes/Shape.h"
// include allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
// include scene and following component
#include "scene/sceneManager.h"
#include <stdbool.h>

Game *New_Game()
{
    Game *game = (Game *)malloc(sizeof(Game));
    game->execute = execute;
    game->game_init = game_init;
    game->game_update = game_update;
    game->game_draw = game_draw;
    game->game_destroy = game_destroy;
    game->title = "Final Project 10xxxxxxx";
    game->display = NULL;
    game->game_init(game);
    return game;
}
void execute(Game *self)
{
    // main game loop
    bool run = true;
    while (run)
    {
        // process all events here
        al_wait_for_event(event_queue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
        {
            run &= self->game_update(self);
            self->game_draw(self);
            break;
        }
        case ALLEGRO_EVENT_DISPLAY_CLOSE: // stop game
        {
            run = false;
            break;
        }
        case ALLEGRO_EVENT_KEY_DOWN:
        {
            key_state[event.keyboard.keycode] = true;
            break;
        }
        case ALLEGRO_EVENT_KEY_UP:
        {
            key_state[event.keyboard.keycode] = false;
            break;
        }
        case ALLEGRO_EVENT_MOUSE_AXES:
        {
            mouse.x = event.mouse.x;
            mouse.y = event.mouse.y;
            break;
        }
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        {
            mouse_state[event.mouse.button] = true;
            break;
        }
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        {
            mouse_state[event.mouse.button] = false;
            break;
        }
        default:
            break;
        }
    }
}
void game_init(Game *self)
{
    printf("Game Initializing...\n");
    GAME_ASSERT(al_init(), "failed to initialize allegro.");
    // initialize allegro addons
    bool addon_init = true;
    addon_init &= al_init_primitives_addon();
    addon_init &= al_init_font_addon();   // initialize the font addon
    addon_init &= al_init_ttf_addon();    // initialize the ttf (True Type Font) addon
    addon_init &= al_init_image_addon();  // initialize the image addon
    addon_init &= al_init_acodec_addon(); // initialize acodec addon
    addon_init &= al_install_keyboard();  // install keyboard event
    addon_init &= al_install_mouse();     // install mouse event
    addon_init &= al_install_audio();     // install audio event
    GAME_ASSERT(addon_init, "failed to initialize allegro addons.");
    // Create display
    self->display = al_create_display(WIDTH, HEIGHT);
    GAME_ASSERT(self->display, "failed to create display.");
    // Create first scene
    create_scene(Menu_L);
    // create event queue
    event_queue = al_create_event_queue();
    GAME_ASSERT(event_queue, "failed to create event queue.");
    // Initialize Allegro settings
    al_set_window_position(self->display, 0, 0);
    al_set_window_title(self->display, self->title);
    // Register event
    al_register_event_source(event_queue, al_get_display_event_source(self->display)); // register display event
    al_register_event_source(event_queue, al_get_keyboard_event_source());             // register keyboard event
    al_register_event_source(event_queue, al_get_mouse_event_source());                // register mouse event
    // register timer event
    fps = al_create_timer(1.0 / FPS);
    al_register_event_source(event_queue, al_get_timer_event_source(fps));
    al_start_timer(fps);
    // initialize the icon on the display
    ALLEGRO_BITMAP *icon = al_load_bitmap("assets/image/icon.jpg");
    al_set_display_icon(self->display, icon);
}
bool game_update(Game *self)
{
    scene->Update(scene);
    if (scene->scene_end)
    {
        scene->Destroy(scene);
        switch (window)
        {
        case 0:
            create_scene(Menu_L);
            break;
        case 1:
            create_scene(GameScene_L);
            break;
        case -1:
            return false;
        default:
            break;
        }
    }
    return true;
}
void game_draw(Game *self)
{
    // Flush the screen first.
    al_clear_to_color(al_map_rgb(100, 100, 100));
    scene->Draw(scene);
    al_flip_display();
}
void game_destroy(Game *self)
{
    // Make sure you destroy all things
    al_destroy_event_queue(event_queue);
    al_destroy_display(self->display);
    scene->Destroy(scene);
    free(self);
}
