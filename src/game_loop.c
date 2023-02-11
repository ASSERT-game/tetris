/***************************************************************************
 * FILENAME:    game_loop.c
 * DESCRIPTION: Handles the initialization and loop for tetris.
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

typedef struct	s_game_scene
{
	SDL_bool	paused;
	int			score;
	int			ticks;

	int			level;

	int				at;
	t_tetris_piece	queue[4];

	SDLX_noise		generator;

	SDLX_Sprite		pieces[ROWS][COLUMNS];

	t_board			board;
}				t_game_scene;

void	*level_init(SDLX_scene_cxt *context, SDL_UNUSED void *addr)
{
	t_game_scene	*scene;

	scene = SDLX_NewScene(sizeof(*scene), context, NULL, level_close, level_update);
	context->score_num1 = 0;

	scene->paused = SDL_FALSE;
	scene->score = 0;
	scene->ticks = 0;

	scene->level = 0;
	scene->generator = SDLX_noise_seed(42, SDLX_NOISE_LATEST);

	size_t	i;
	size_t	j;
	int		padding;
	int		offset_x;
	int		offset_y;
	int		size;
	size_t	counter;

	i = 0;
	padding = 2;
	counter = 0;
	size = 16;
	offset_x = ((WIN_WIDTH / DISPLAY_SCALE) - ((size + padding) * COLUMNS)) / 2;
	offset_y = ((WIN_HEIGHT / DISPLAY_SCALE) - ((size + padding) * ROWS)) / 2;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLUMNS)
		{
			scene->board[i][j].active = SDL_FALSE;
			scene->board[i][j].color = (SDL_Color){100 + i * 5, 100, 100, 1};

			scene->pieces[i][j] = SDLX_Sprite_Static(ASSETS"/piece.png");

			scene->pieces[i][j].dst = SDLX_NULL_SELF;
			scene->pieces[i][j]._dst = (SDL_Rect){j * (size + padding) + offset_x, i * (size + padding) + offset_y, size, size};

			// if (scene->generator.value % 100 > 90)
				// scene->board[i][j].active = SDL_TRUE;

			// SDLX_noise_next(&(scene->generator), SDLX_NOISE_LATEST);

			counter++;
			j++;
		}
		i++;
	}

	scene->at = 0;

	square_type(&(scene->queue[0]));

	// scene->queue[0].y = 0;
	// l_type2(&(scene->queue[0]));

	return (NULL);
}

void	*level_close(SDLX_scene_cxt *context, void *vp_scene)
{
	t_game_scene	*scene;

	scene = vp_scene;

	context->score_num1 = scene->score;

	return (NULL);
}

void	*level_update(SDLX_scene_cxt *context, SDL_UNUSED void *vp_scene)
{
	t_game_scene	*scene;

	scene = context->scene_meta;

	int		i;
	int		j;
	size_t	counter;
	int		red, green, blue;

	i = 0;
	counter = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLUMNS)
		{
			if (scene->board[i][j].active == SDL_TRUE)
			{
				red = scene->board[i][j].color.r;
				green = scene->board[i][j].color.g;
				blue = scene->board[i][j].color.b;
				SDL_SetTextureColorMod(scene->pieces[i][j].sprite_data[0].texture, red, green, blue);
				SDLX_RenderQueue_Add(NULL, &(scene->pieces[i][j]));
			}
			counter++;
			j++;
		}
		i++;
	}

	int y_offset;
	int x_offset;

	if (scene->ticks % 10 == 0)
		scene->queue[0].y++;
	else if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, DPAD_DOWN))
		scene->queue[0].y++;

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, DPAD_LEFT) && scene->queue[0].x > 0)
		scene->queue[0].x--;

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, DPAD_RIGHT)  && scene->queue[0].x + 1 < COLUMNS)
		scene->queue[0].x++;


	x_offset = scene->queue[0].x;
	y_offset = scene->queue[0].y;


	i = 3;
	while (i >= 0)
	{
		j = 0;
		if (should_anchor(&(scene->queue[0]), &(scene->board)))
		{
			j = 10;
			i = -10;
			anchor_pieces(&(scene->queue[0]), &(scene->board));
			scene->queue[0].y = 0;
		}

		while (j < 4)
		{
			if (scene->queue[0].shape[i][j] == 'x')
			{
				// SDL_SetTextureColorMod(scene->pieces[i + y_offset][j + x_offset].sprite_data[0].texture, red, green, blue);
				SDL_SetTextureColorMod(scene->pieces[i + y_offset][j + x_offset].sprite_data[0].texture, 250, 0, 0);
				SDLX_RenderQueue_Add(NULL, &(scene->pieces[i + y_offset][j + x_offset]));
			}
			j++;
		}

		i--;
	}

	// SDL_Log("Ticks %d", scene->ticks);

	scene->ticks++;

	return (NULL);
}
