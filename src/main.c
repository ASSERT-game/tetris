/***************************************************************************
 * FILENAME:    main.c
 * DESCRIPTION: Main file for tetris
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 04Aug2022
***************************************************************************/

#include "main.h"

void	tetris_init(t_tetris_perma *tetris)
{
	g_SDLX_Context.shouldQuit = SDL_FALSE;

	g_SDLX_Context.init_fn = level_init;

	g_SDLX_Context.perma_meta = tetris;

	g_GameInput.key_mapper.map_arr = tetris_key_map(&(g_GameInput.key_mapper.amount));

}

int main(void)
{
	t_tetris_perma	tetris;

	SDLX_GetDisplay();
	tetris_init(&(tetris));
	while (g_SDLX_Context.shouldQuit == SDL_FALSE)
		SDLX_MainSceneLoop_Post(&(g_SDLX_Context));

	return (EXIT_SUCCESS);
}
