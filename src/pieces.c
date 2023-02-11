/***************************************************************************
 * FILENAME:    pieces.c
 * DESCRIPTION: Pieces
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 05Aug2022
***************************************************************************/

#include "main.h"

void	print_piece(t_tetris_piece *piece)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		SDL_Log("String %c%c%c%c", piece->shape[i][0], piece->shape[i][1], piece->shape[i][2], piece->shape[i][3]);
		i++;
	}
}

t_tetris_piece	*t_type(t_tetris_piece *piece)
{
	SDL_memcpy(piece->shape[0], "xxx.", sizeof(piece->shape[0]));
	SDL_memcpy(piece->shape[1], ".x..", sizeof(piece->shape[1]));
	SDL_memcpy(piece->shape[2], "....", sizeof(piece->shape[2]));
	SDL_memcpy(piece->shape[3], "....", sizeof(piece->shape[3]));
	return (piece);
}

t_tetris_piece	*l_type1(t_tetris_piece *piece)
{
	SDL_memcpy(piece->shape[0], "xxx.", sizeof(piece->shape[0]));
	SDL_memcpy(piece->shape[1], "..x.", sizeof(piece->shape[1]));
	SDL_memcpy(piece->shape[2], "....", sizeof(piece->shape[2]));
	SDL_memcpy(piece->shape[3], "....", sizeof(piece->shape[3]));
	return (piece);
}

t_tetris_piece	*l_type2(t_tetris_piece *piece)
{
	SDL_memcpy(piece->shape[0], "xxx.", sizeof(piece->shape[0]));
	SDL_memcpy(piece->shape[1], "x...", sizeof(piece->shape[1]));
	SDL_memcpy(piece->shape[2], "....", sizeof(piece->shape[2]));
	SDL_memcpy(piece->shape[3], "....", sizeof(piece->shape[3]));
	return (piece);
}

t_tetris_piece	*long_type(t_tetris_piece *piece)
{
	SDL_memcpy(piece->shape[0], "xxxx", sizeof(piece->shape[0]));
	SDL_memcpy(piece->shape[1], "....", sizeof(piece->shape[1]));
	SDL_memcpy(piece->shape[2], "....", sizeof(piece->shape[2]));
	SDL_memcpy(piece->shape[3], "....", sizeof(piece->shape[3]));
	return (piece);
}

t_tetris_piece	*z_type1(t_tetris_piece *piece)
{
	SDL_memcpy(piece->shape[0], "xx..", sizeof(piece->shape[0]));
	SDL_memcpy(piece->shape[1], ".xx.", sizeof(piece->shape[1]));
	SDL_memcpy(piece->shape[2], "....", sizeof(piece->shape[2]));
	SDL_memcpy(piece->shape[3], "....", sizeof(piece->shape[3]));
	return (piece);
}

t_tetris_piece	*z_type2(t_tetris_piece *piece)
{
	SDL_memcpy(piece->shape[0], ".xx.", sizeof(piece->shape[0]));
	SDL_memcpy(piece->shape[1], "xx..", sizeof(piece->shape[1]));
	SDL_memcpy(piece->shape[2], "....", sizeof(piece->shape[2]));
	SDL_memcpy(piece->shape[3], "....", sizeof(piece->shape[3]));
	return (piece);
}

t_tetris_piece	*square_type(t_tetris_piece *piece)
{
	SDL_memcpy(piece->shape[0], "xx..", sizeof(piece->shape[0]));
	SDL_memcpy(piece->shape[1], "xx..", sizeof(piece->shape[1]));
	SDL_memcpy(piece->shape[2], "....", sizeof(piece->shape[2]));
	SDL_memcpy(piece->shape[3], "....", sizeof(piece->shape[3]));
	return (piece);
}

void		anchor_pieces(t_tetris_piece *piece, t_board *board)
{
	int i;
	int j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (piece->shape[i][j] == 'x' && i + piece->y < ROWS)
				(*board)[i + piece->y][j + piece->x].active = SDL_TRUE;
			j++;
		}
		i++;
	}
}

SDL_bool	should_anchor(t_tetris_piece *piece, t_board *board)
{
	int		i;
	int		j;
	int		x_offset;
	int		y_offset;

	i = 0;
	x_offset = piece->x;
	y_offset = piece->y;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (piece->shape[i][j] == 'x')
			{
				if (i + y_offset + 1 >= ROWS)
					return SDL_TRUE;
				if ((*board)[i + y_offset + 1][j + x_offset].active == SDL_TRUE)
					return SDL_TRUE;
			}
			j++;
		}
		i++;
	}

	return (SDL_FALSE);
}