#define ALLEGRO_NO_MAGIC_MAIN
#include "GameWindow.h"

​int real_main(int argc, char **argv)
{
   Game_establish();
}

int main(int argc, char **argv)
{
   return al_run_main(argc, argv, real_main);
}