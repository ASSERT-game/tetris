/***************************************************************************
 * FILENAME:    main.h
 * DESCRIPTION: Header File for tetris
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 04Aug2022
***************************************************************************/

#ifndef MAIN_STRUCTS_H
# define MAIN_STRUCTS_H

# include "SDLX.h"

//		T Type
//					 X X X .
//					 . X . .
//					 . . . .
//					 . . . .

//		L Type1
//					 X X X .
//					 . . X .
//					 . . . .
//					 . . . .

//		L Type2
//					 X X X .
//					 X . . .
//					 . . . .
//					 . . . .

//		Long Type
//					 X X X X
//					 . . . .
//					 . . . .
//					 . . . .

//		Z Type1
//					 X X . .
//					 . X X .
//					 . . . .
//					 . . . .

//		Z Type2
//					 . X X .
//					 X X . .
//					 . . . .
//					 . . . .

//		Square Type
//					 X X . .
//					 X X . .
//					 . . . .
//					 . . . .

#define	ROWS (20)
#define	COLUMNS (10)

typedef struct	s_tetris_piece
{
	// int			type;
	char		shape[4][4];

	int			x;
	int			y;

	SDL_Color	color;
}				t_tetris_piece;

typedef struct	s_piece
{
	SDL_bool	active;
	SDL_Color	color;
}				t_piece;

typedef	t_piece t_board[ROWS][COLUMNS];

typedef struct	s_tetris_perma
{

}				t_tetris_perma;


#endif