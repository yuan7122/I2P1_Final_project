#include "GameWindow.h"
int main(int argc, char **argv)
{
	Game *game = New_Game();
	game->execute(game);
	game->game_destroy(game);
	return 0;
}
