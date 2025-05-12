#ifndef GAME_ASSERT_H_INCLUDED
#define GAME_ASSERT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/system.h>

/**
 * @brief Assert function for the game.
 * @details The assert function will terminate the game and print (1) where the assert happens and (2) your custom message.
 * The custom message accepts printf format for a more convenient style to print out.
 */
#define GAME_ASSERT(condition, ...)                                                 \
	{                                                                               \
		if (!(condition))                                                           \
		{                                                                           \
			fprintf(stderr, "Error at line. %d in file %s.\n", __LINE__, __FILE__); \
			fprintf(stderr, "Error message: ");                                     \
			fprintf(stderr, __VA_ARGS__);                                           \
			fputs("", stderr);                                                      \
			al_uninstall_system();                                                  \
			exit(1);                                                                \
		}                                                                           \
	}

#endif
