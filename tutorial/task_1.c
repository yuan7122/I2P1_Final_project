/*

GOAL:
Create a display window.

*/
#include <stdio.h>
#include <allegro5/allegro.h>

/*
    TODO: Declare display variable.
*/

const int width = 800;
const int height = 600;

void show_err_msg(int msg);
void game_init();
void game_begin();
void game_destroy();


int main(int argc, char *argv[]) {

    printf("Hello world!!!\n");

    game_init();

    al_rest(5);

    game_begin();

    al_rest(5);
    printf("See you, world!!\n");

    game_destroy();
    return 0;
}


void show_err_msg(int msg) {
    fprintf(stderr, "unexpected msg: %d", msg);
    game_destroy();
    exit(9);
}
/*
    The function above aims to show the error message and terminate the game.
    You may use it in any function need to deal with some error message.
    The program would not get any error if you don't utilize it,
    But you may get a tough debugging time when some mistakes happen.
    You can modify it to fit for your habit.
*/

void game_init() {
    if ( !al_init() ) {
        show_err_msg(-1);
    }

    /*
        TODO: Create your display variable.
    */
}

void game_begin() {
    /*
        TODO: Fill the whole window with an arbitrary color, and show the window
    */
}
void game_destroy() {
    /*
        TODO: Destroy everything you have initialized or created.
    */
}
