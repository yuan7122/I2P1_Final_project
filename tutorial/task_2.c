/*

GOAL:
Draw a picture, a rectangle and some text.

*/
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

/*
    TODO: Include the head files containing the fuctions we want to use
*/

ALLEGRO_DISPLAY* display = NULL;

/*
    TODO: Declare the variable of font and image.
*/


const int width = 800;
const int height = 600;

const int img_width = 640;
const int img_height = 480;

void show_err_msg(int msg);
void game_init();
void game_begin();
void game_destroy();


int main(int argc, char *argv[]) {
    int msg = 0;

    game_init();
    game_begin();
    printf("Hello world!!!\n");
    al_rest(10);

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

    display = al_create_display(width, height);
    if ( display == NULL ) {
        show_err_msg(-1);
    }

    al_init_primitives_addon();
    /*
        TODO: Initialize the image and the font.
    */

}

void game_begin() {
    al_clear_to_color(al_map_rgb(100,100,100));
    /*
        TODO: Load and draw all!!!
    */
    al_flip_display();
}
void game_destroy() {
    al_destroy_display(display);
}
