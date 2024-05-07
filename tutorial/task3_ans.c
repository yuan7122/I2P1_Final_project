#include <stdio.h>
#include <allegro5/allegro.h>

#define GAME_TERMINATE 666


#define AL_INIT_FAILED -1
#define DESPLAY_INIT_FAILED -2

ALLEGRO_DISPLAY* display = NULL;

/*
 * TODO: Declare your event_queue and event.
 */
//ANS: declare event queue
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;


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
    al_set_window_position(display, 0, 0);
    if ( display == NULL ) {
        show_err_msg(DESPLAY_INIT_FAILED);
    }

    /*
     * TODO: initial display and event queue, and register specific event into event queue.
     */
     //ANS: register event
     event_queue = al_create_event_queue();
     al_register_event_source(event_queue, al_get_display_event_source(display));

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
    al_wait_for_event(event_queue, &event);
    if( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ){
    return GAME_TERMINATE;
    }
    return 1;
}

int game_run() {
    /*
     * TODO: Judge whether there's any event in the queue; if so, call process_event() to process it.
     */
     // ANS: use al_is_event_queue_empty(ALLEGRO_EVENT_QUEUE*)
     if( !al_is_event_queue_empty(event_queue) ){
        return process_event();
     }
     return 1;
}

void game_destroy() {
    /*
     * TODO: Destroy all thing you have created.
     */
     // ANS: destroy event queue
     al_destroy_event_queue(event_queue);
}
