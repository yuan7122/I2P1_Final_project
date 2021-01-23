/*

GOAL:
Create a event_queue and make close window by the up right corner cross possible.

*/

#include <stdio.h>
#include <allegro5/allegro.h>

#define GAME_TERMINATE 666


#define AL_INIT_FAILED -1
#define DESPLAY_INIT_FAILED -2

ALLEGRO_DISPLAY* display = NULL;



/*
 * TODO: Declare your event_queue and event.
 */

const int width = 800;
const int height = 600;

void show_err_msg(int msg);
void game_init();
void game_begin();
int process_event();
int game_run();
void game_destroy();


int main(int argc, char *argv[]) {
    int msg = 0;

    game_init();
    game_begin();
    printf("Hello world!!!\n");
    printf("Close window to terminate.\n");

    while ( msg != GAME_TERMINATE ) {
        msg = game_run();
        if ( msg == GAME_TERMINATE )
            printf("See you, world\n");
    }
    game_destroy();
    return 0;
}

void show_err_msg(int msg) {
    fprintf(stderr, "unexpected msg: %d", msg);
    game_destroy();
    exit(9);
}

void game_init() {
    if ( !al_init() ) {
        show_err_msg(AL_INIT_FAILED);
    }

    display = al_create_display(width, height);
    if ( display == NULL ) {
        show_err_msg(DESPLAY_INIT_FAILED);
    }

    /*
     * TODO: initial display and event queue, and register specific event into event queue.
     */
}

void game_begin() {
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
}

int process_event() {
    /*
     * TODO: Get the earliest event from event_queue and judge whether it represents the closing of window.
     *       If so, return GAME_TERMINATE.
     * Hint: using event.type == ALLEGRO_EVENT_DISPLAY_CLOSE to judge whether the display is closed just now.
     */
}

int game_run() {
    /*
     * TODO: Judge whether there's any event in the queue; if so, call process_event() to process it.
     */
}

void game_destroy() {
    /*
     * TODO: Destroy all thing you have created.
     */
}
