/***************************************************************************
 * FILENAME:    tetris_input.c
 * DESCRIPTION: Handles the input for tetris
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

SDLX_iMap	*tetris_key_map(size_t *size)
{
	static SDLX_iMap	key_map[] =
	{
		(SDLX_iMap){&BMAP(button_DPAD_UP),		1, SDL_SCANCODE_UP},
		(SDLX_iMap){&BMAP(button_DPAD_LEFT),	1, SDL_SCANCODE_LEFT},
		(SDLX_iMap){&BMAP(button_DPAD_DOWN),	1, SDL_SCANCODE_DOWN},
		(SDLX_iMap){&BMAP(button_DPAD_RIGHT),	1, SDL_SCANCODE_RIGHT},

		(SDLX_iMap){&BMAP(button_DPAD_UP),		1, SDL_SCANCODE_W},
		(SDLX_iMap){&BMAP(button_DPAD_LEFT),	1, SDL_SCANCODE_A},
		(SDLX_iMap){&BMAP(button_DPAD_DOWN),	1, SDL_SCANCODE_S},
		(SDLX_iMap){&BMAP(button_DPAD_RIGHT),	1, SDL_SCANCODE_D},

		(SDLX_iMap){&BMAP(button_START),		1, SDL_SCANCODE_P},
	};

	*size = sizeof(key_map) / sizeof(*key_map);
	return (&key_map[0]);
}