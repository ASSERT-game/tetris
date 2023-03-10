/***************************************************************************
 * FILENAME:	SDLX_structs.h
 * DESCRIPTION: Structures to be used by SDLX and external files.
 *
 * ENVIRONMENT:
 *	 macOS High Sierra 10.13.6
 *	 Visual Studio Code 1.52.1
 * AUTHORS:
 *	 Kevin Colour
 * DATES:
 *	 Created: 24Jan2021
***************************************************************************/

#ifndef SDLX_structs_H
#define SDLX_structs_H

# include "SDL2/SDL.h"

# include "SDLX_const.h"

#define SDLX_NULL_SELF ((void *)(1))

typedef struct SDLX_Display
{
	SDL_Renderer	*renderer;
	SDL_Window		*window;
}	SDLX_Display;

typedef struct SDLX_Sprite_Data
{
	SDL_Texture		*texture;
	SDL_Rect		_src;
	SDL_Rect		*src;
	size_t			cycle;
	size_t			skip;
}	SDLX_Sprite_Data;

typedef struct SDLX_Sprite
{
	SDLX_Sprite_Data	*sprite_data;

	size_t				current;
	SDL_Rect			_dst;
	SDL_Rect			*dst;

	double				angle;
	SDL_Point			_center;
	SDL_Point			*center;
	SDL_RendererFlip	flip;

	size_t				id;
	int					sort;
}	SDLX_Sprite;

typedef struct SDLX_RenderQueue
{
	size_t			index;
	size_t			capacity;

	SDLX_Sprite		**content;
}	SDLX_RenderQueue;

extern SDLX_RenderQueue	default_RenderQueue;
typedef struct	SDLX_iMap
{
	int			*dest;
	int			values;
	int			param;
}				SDLX_iMap;

typedef struct	SDLX_input_mapper
{
	size_t		amount;

	SDLX_iMap	*map_arr;
}				SDLX_input_mapper;

typedef struct	SDLX_GameInput
{
	SDLX_input_mapper	key_mapper;
	SDLX_input_mapper	pad_mapper;
	SDL_bool			pad_last;

	const Uint8			*keystate;


	struct
	{
		int	button_A;
		int	button_B;
		int	button_X;
		int	button_Y;
		int	button_BACK;
		int	button_GUIDE;
		int	button_START;
		int	button_LEFTSTICK;
		int	button_RIGHTSTICK;
		int	button_LEFTSHOULDER;
		int	button_RIGHTSHOULDER;
		int	button_DPAD_UP;
		int	button_DPAD_DOWN;
		int	button_DPAD_LEFT;
		int	button_DPAD_RIGHT;

		int	button_num0;
		int	button_num1;
		int	button_num2;
		int	button_num3;
		int	button_num4;
		int	button_num5;
		int	button_num6;
		int	button_num7;
		int	button_num8;
		int	button_num9;

		SDL_Point primary;
		SDL_Point primary_delta;

		int	button_primleft;
		int	button_primright;

		SDL_Point	second;

		int			button_secleft;
		int			button_secright;

		SDL_Point	leftaxis;
		SDL_Point	rightaxis;

		/* these are axis-like while the one below are 'button' like */
		int	trigger_left;
		int	trigger_right;

		int			button_left_trigger;
		int			button_right_trigger;


	}	GameInput;
}				SDLX_GameInput;

extern SDLX_GameInput	g_GameInput;
extern SDLX_GameInput	g_GameInput_prev;

#define BMAP(button) (g_GameInput.GameInput.button)
#define SDLX_GAME_PRESS(curr, prev, button) ((curr.GameInput.button_##button != 0 && prev.GameInput.button_##button == 0))
#define SDLX_GAME_RELEASE(curr, prev, button) ((curr.GameInput.button_##button == 0 && prev.GameInput.button_##button >= 1))
#define SDLX_INPUT_CONSUME(curr, prev, button) {curr.GameInput.button_##button = -1; prev.GameInput.button_##button = -1;}

enum	SDLX_DIR
{
	SDLX_DIR_NONE	= 0x0000,

	/* These have the properties of Euclidian direction. */
	SDLX_ELEFT		= 0x00FF,
	SDLX_ERIGHT		= 0x0001,
	SDLX_EUP		= 0x0100,
	SDLX_EDOWN		= 0xFF00,

	/* These are made with the caution that arrays reverse up and down. */
	SDLX_ALEFT		= SDLX_ELEFT,
	SDLX_ARIGHT		= SDLX_ERIGHT,
	SDLX_AUP		= SDLX_EDOWN,
	SDLX_ADOWN		= SDLX_EUP,

	SDLX_LEFT		= SDLX_ALEFT,
	SDLX_RIGHT		= SDLX_ARIGHT,
	SDLX_UP			= SDLX_AUP,
	SDLX_DOWN		= SDLX_ADOWN,
};

typedef union SDLX_direction
{
	int			val;
	struct
	{
		int8_t	x;
		int8_t	y;
	}			c;
}	SDLX_direction;

typedef struct	SDLX_button
{
	SDLX_RenderQueue	*render_dst;

	int			(*sprite_fn)(SDLX_Sprite_Data **, int);
	SDLX_Sprite	sprite;
	SDL_Rect	trigger_box;

	int			norm_no;
	int			focus_no;
	SDL_bool	isLocked;

	SDL_bool	isDisabled;

	SDL_bool	isGloballyActive;
	SDL_bool	isFocused;
	SDL_bool	isTriggered;

	void		*meta;
	void		*meta1;
	int			meta_length;

	SDL_bool	(*get_focus_fn)(struct SDLX_button *, void *, size_t);

	void		*(*focus_fn)(struct SDLX_button *, void *, size_t);
	void		*(*focus_once_fn)(struct SDLX_button *, void *, size_t);
	void		*(*trigger_fn)(struct SDLX_button *, void *, size_t);
	void		*(*update_fn)(struct SDLX_button *, void *, size_t);

	//set_states_function //What for?

	void		*up;
	void		*down;
	void		*left;
	void		*right;

	// Currently not used:
	int			priority;
	char		*text;	//Might be another structure

}				SDLX_button;

typedef struct	SDLX_collision
{
	size_t		type;
	double		angle;
	SDL_Rect	hitbox;
	SDL_Rect	*hitbox_ptr;
	SDL_Point	center;
	SDL_Point	*center_ptr;

	size_t		response_amount;
	size_t		*response_type;

	void		*originator;

	void		*detect_meta1;
	void		*detect_meta2;

	void		*engage_meta1;
	void		*engage_meta2;

	void		*(*engage)(void *, void *, void *, void *);
	SDL_bool	(*detect)(void *, void *, void *, void *);

}				SDLX_collision;

typedef struct	SDLX_collision_bucket
{
	size_t		type;

	size_t		index;
	size_t		capacity;

	SDLX_collision	**content;
}				SDLX_collision_bucket;

extern SDLX_collision_bucket	default_CollisionBucket;

struct SDLX_scene_cxt;
typedef void *(SDLX_scene_fn)(struct SDLX_scene_cxt *, void *);

typedef struct	SDLX_scene_cxt
{
	SDL_bool	shouldQuit;
	SDL_bool	shouldChange;

	TTF_Font	*def_font;
	TTF_Font	*def_font_outline;

	int			score_num1;
	int			ticks_num2;
	int			reset_num3;
	int			level_num4;

/* Extra numbers in case the user wants to save extraneous information */

	int			extra_num5;
	int			extra_num6;
	int			extra_num7;
	int			extra_num8;

	void		*perma_meta;
	void		*scene_meta;

	void		*meta1;
	void		*meta2;

	SDLX_scene_fn	*init_fn;
	SDLX_scene_fn	*update_fn;
	SDLX_scene_fn	*close_fn;

	SDL_Color		background_color;
	SDLX_Sprite		background;
	SDL_Texture		*capture_texture;
}				SDLX_scene_cxt;

extern SDLX_scene_cxt	g_SDLX_Context;

typedef struct	SDLX_post_process
{
	double		scale;
	double		angle;

	int			x_offset;
	int			y_offset;

	int			duration;
	int			current_tick;

	SDL_bool	shouldPostProcess;

	SDL_Texture		*post_process;
}				SDLX_post_process;

extern SDLX_post_process	g_PostProcess;

enum	SDLX_dynamic_ops
{
	SDLX_AXM_NOP,
	SDLX_AXM_EQL,
	SDLX_AXM_ADD,
	SDLX_AXM_SUB,
	SDLX_AXM_MUL,
	SDLX_AXM_DIV,
	SDLX_AXM_MOD,
	SDLX_AXM_XOR,
	SDLX_AXM_AND,
	SDLX_AXM_OR,
	SDLX_AXM_SHIFT_LEFT,
	SDLX_AXM_SHIFT_RIGHT,
};

typedef	void (SDLX_dynamic_logic_fn)(int *, int);
extern SDLX_dynamic_logic_fn	*SDLX_xlogic[];

typedef enum	SDLX_noise_version
{
	SDLX_NOISE_V1,
	SDLX_NOISE_VERSION_NULL,

	SDLX_NOISE_LATEST = SDLX_NOISE_V1,
}				SDLX_noise_version;

typedef struct	SDLX_noise
{
	uint32_t	value;
	char		alloc[24];
}				SDLX_noise;

#endif
