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
bool key_state[ALLEGRO_KEY_MAX];
void show_err_msg(int msg);
void game_init();
void game_begin();
void game_draw();
int game_update();
int process_event();
int game_run();
void game_destroy();

/*
    You can declare some variables here if it is useful for you.
*/
int move = 0;


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
    al_install_keyboard();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
}
void game_draw(){
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255,0,255));
    al_flip_display();
}
void game_begin() {
    game_draw();
}


int keyboard_event(){
    if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;

    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
    return 0;
}
int game_update(){
    if( key_state[ALLEGRO_KEY_W] ){
        pos_y -= 10;
    }else if( key_state[ALLEGRO_KEY_A] ){
        pos_x -= 10;
    }else if( key_state[ALLEGRO_KEY_S] ){
        pos_y += 10;
    }else if( key_state[ALLEGRO_KEY_D] ){
        pos_x += 10;
    }else if( key_state[ALLEGRO_KEY_ESCAPE] ){
        return GAME_TERMINATE;
    }
    return 0;
}
int process_event() {
    al_wait_for_event(event_queue, &event);
    /*
        TODO: Process the mouse event.
        Seperate the processing of click event and moving event is encouraged.
    */
    keyboard_event();
    int error = game_update();
    game_draw();
    return error;
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
