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

#ifndef MAIN_H
# define MAIN_H

# include "SDLX.h"
# include "main_structs.h"

#define	ASSETS "assets"

void	*level_init(SDLX_scene_cxt *context, SDL_UNUSED void *addr);
void	*level_close(SDLX_scene_cxt *context, void *vp_scene);
void	*level_update(SDLX_scene_cxt *context, SDL_UNUSED void *vp_scene);

t_tetris_piece	*t_type(t_tetris_piece *piece);
t_tetris_piece	*l_type1(t_tetris_piece *piece);
t_tetris_piece	*l_type2(t_tetris_piece *piece);
t_tetris_piece	*long_type(t_tetris_piece *piece);
t_tetris_piece	*z_type1(t_tetris_piece *piece);
t_tetris_piece	*z_type2(t_tetris_piece *piece);
t_tetris_piece	*square_type(t_tetris_piece *piece);

void	print_piece(t_tetris_piece *piece);

SDLX_iMap	*tetris_key_map(size_t *size);
void		anchor_pieces(t_tetris_piece *piece, t_board *board);
SDL_bool	should_anchor(t_tetris_piece *piece, t_board *board);

#endif