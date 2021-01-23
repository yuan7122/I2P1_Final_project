#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>              //Our primitive header file

#define GAME_TERMINATE 666


ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;




const int width = 800;
const int height = 600;

int pos_x, pos_y; // The position of rectangle's left-up corner.

void show_err_msg(int msg);
void game_init();
void game_begin();
int process_event();
int game_run();
void game_destroy();

/*
    You can declare some variables here if it is useful for you.
*/
bool show_box = true;


int main(int argc, char *argv[]) {
    int msg = 0;

    game_init();
    game_begin();
    printf("Hello world!!!\n");

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
        show_err_msg(-1);
    }

    pos_x = width / 2;
    pos_y = height / 2;

    display = al_create_display(width, height);
    al_set_window_position(display, 0, 0);
    event_queue = al_create_event_queue();

    if ( display == NULL || event_queue == NULL ) {
        show_err_msg(-1);
    }

    /*
        TODO: Something need to be created, initialized and registered.
    */
    al_init_primitives_addon();
    al_install_mouse();
    al_register_event_source(event_queue, al_get_mouse_event_source());
}

void game_begin() {
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255,0,255));
    al_flip_display();
}

int process_event() {
    al_wait_for_event(event_queue, &event);
    /*
        TODO: Process the mouse event.
        Seperate the processing fo click event and moving event is encouraged.
    */
    if( event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
        if( event.mouse.button == 1 ){
            show_box = !show_box;
        }else if( event.mouse.button == 2 ){
            return GAME_TERMINATE;
        }
    }
    if( event.type == ALLEGRO_EVENT_MOUSE_AXES ){
        pos_x = event.mouse.x;
        pos_y = event.mouse.y;
    }
    al_clear_to_color(al_map_rgb(0,0,0));
    if( show_box )
        al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255,0,255));
    al_flip_display();
    return 0;
}

int game_run() {
    int error = 0;
    if ( !al_is_event_queue_empty(event_queue) ) {
        error = process_event();
    }
    return error;
}

void game_destroy() {
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
}
