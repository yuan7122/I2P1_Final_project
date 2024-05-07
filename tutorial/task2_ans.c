#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


/*
    TODO: Include the head files containing the functions we want to use
*/
#include <allegro5/allegro_font.h> // ANS: include the head file of font
#include <allegro5/allegro_ttf.h> // ANS: include the head file of ttf
#include <allegro5/allegro_image.h>// ANS: include the head file of image


ALLEGRO_DISPLAY* display = NULL;

/*
    TODO: Declare the variable of font and image.
*/
ALLEGRO_FONT *font; // ANS: declare font variable
ALLEGRO_BITMAP *img; // ANS: declare image variable

const int width = 800;
const int height = 600;

const int img_width = 640;
const int img_height = 480;

void show_err_msg(int msg);
void game_init();
void game_begin();
void game_destroy();


int main(int argc, char *argv[]) {

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
    al_set_window_position(display, 0, 0);
    if ( display == NULL ) {
        show_err_msg(-1);
    }

    al_init_primitives_addon();
    /*
        TODO: Initialize the image and the font.
    */
    al_init_font_addon(); // ANS: initialize font
    al_init_ttf_addon(); // ANS: initialize ttf
    al_init_image_addon();//ANS: initialize image

}

void game_begin() {
    al_clear_to_color(al_map_rgb(100,100,100));
    /*
        TODO: Load and draw all!!!
    */
    font = al_load_ttf_font("pirulen.ttf", 20, 0); // ANS: load font
    al_draw_text(font, al_map_rgb(255,255,255), width-200, height-50, ALLEGRO_ALIGN_CENTRE,  "answer"); // ANS: draw some text
    al_draw_rectangle(width-300, height-50, width, height, al_map_rgb(255,255,255), 2); // ANS: draw rectangle
    img = al_load_bitmap("htchen.jpg"); // ANS: load image
    al_draw_bitmap(img, 0, 0, 0); // ANS: draw image



    al_flip_display();
}
void game_destroy() {
    al_destroy_display(display);
    al_destroy_bitmap(img); //ANS: destroy image
    al_destroy_font(font); // destroy font

}
