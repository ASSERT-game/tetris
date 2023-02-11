/***************************************************************************
 * FILENAME:    noise.c
 * DESCRIPTION: Makes
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 14May2022
***************************************************************************/

#include "SDLX.h"

typedef struct	_SDLX_noise_v1
{
	uint32_t	value;

	int32_t		x;

	int32_t		step1;
	int32_t		step2;
	int32_t		step3;
	int32_t		step4;
}				_SDLX_noise_v1;

Uint32	SDLX_noise_v1_next(void *noise_addr)
{
	_SDLX_noise_v1	*noise_state;

	noise_state = noise_addr;
	noise_state->step1 += 1431655957;
	noise_state->step2 += 5039;
	noise_state->step3 += 39916801;
	noise_state->step4 += 858993459;

	uint32_t	value = 0;

	value = ((noise_state->step1 & 1294967295) >> 8) + ((noise_state->step1 & 181508891) << 8) +
			((noise_state->step2 & 1294967295) >> 3) + ((noise_state->step2 & 181508891) << 3) +
			((noise_state->step3 & 1294967295) >> 3) + ((noise_state->step3 & 181508891) << 3) +
			((noise_state->step4 & 1294967295) >> 5) + ((noise_state->step4 & 181508891) << 5);

	noise_state->x++;
	noise_state->value = value;
	return (noise_state->value);
}

Uint32	SDLX_noise_v1_prev(void *noise_addr)
{
	_SDLX_noise_v1	*noise_state;

	noise_state = noise_addr;
	noise_state->step1 -= 1431655957;
	noise_state->step2 -= 5039;
	noise_state->step3 -= 39916801;
	noise_state->step4 -= 858993459;

	uint32_t	value = 0;

	value = ((noise_state->step1 & 1294967295) >> 8) + ((noise_state->step1 & 181508891) << 8) +
			((noise_state->step2 & 1294967295) >> 3) + ((noise_state->step2 & 181508891) << 3) +
			((noise_state->step3 & 1294967295) >> 3) + ((noise_state->step3 & 181508891) << 3) +
			((noise_state->step4 & 1294967295) >> 5) + ((noise_state->step4 & 181508891) << 5);

	noise_state->x--;
	noise_state->value = value;
	return (noise_state->value);
}

SDLX_noise	SDLX_noise_v1_seed(Uint32 seed)
{
	SDLX_noise	result;
	_SDLX_noise_v1 noise;
	SDL_assert(sizeof(SDLX_noise) >= sizeof(_SDLX_noise_v1));
	int	value = 0;

	noise.step1 = (seed + 771) * 196611;
	noise.step2 = seed * seed;
	noise.step3 = -seed * seed * seed * 196611;
	noise.step4 = seed * 65535;

	value = ((noise.step1 & 1294967295) >> 8) + ((noise.step1 & 0xFFFFFFFF) << 9) +
			((noise.step2 & 1294967295) >> 3) + ((noise.step2 & 0xFFFFFFFF) << 5) +
			((noise.step3 & 1294967295) >> 3) + ((noise.step3 & 0xFFFFFFFF) << 3) +
			((noise.step4 & 1294967295) >> 5) + ((noise.step4 & 0xFFFFFFFF) << 7);

	noise.x = 0;
	noise.value = value;

	SDL_memcpy(&(result), &(noise), sizeof(noise));
	return (result);
}

void	SDLX_noise_v1_add(void *noise_addr, Sint32 by)
{
	Uint32 i;
	Uint32 stop;
	Uint32 (*iterator_fn)(void *);
	_SDLX_noise_v1	*noise;

	noise = noise_addr;
	iterator_fn = SDLX_noise_v1_next;
	if (by <= 0)
		iterator_fn = SDLX_noise_v1_prev;

	i = 0;
	stop = SDL_abs(by);
	while (i < stop)
	{
		iterator_fn(noise);
		i++;
	}
}

void	SDLX_noise_v1_add_into(Sint32 *dst, void *noise_addr, Sint32 by)
{
	_SDLX_noise_v1	*noise;
	Uint32 i;
	Uint32 stop;
	Uint32 (*iterator_fn)(void *);

	noise = noise_addr;
	iterator_fn = SDLX_noise_v1_next;
	if (by <= 0)
		iterator_fn = SDLX_noise_v1_prev;

	i = 0;
	stop = SDL_abs(by);
	while (i < stop)
	{
		dst[i] = iterator_fn(noise);
		i++;
	}
}

typedef struct	SDLX_noise_functions
{
	SDLX_noise_version	name;

	SDLX_noise	(*seed_fn)(Uint32);
	Uint32		(*next_fn)(void *);
	Uint32		(*prev_fn)(void *);
	void		(*add_fn)(void *, Sint32);
	void		(*add_into_fn)(Sint32 *, void *, Sint32);
}				SDLX_noise_functions;

SDLX_noise_functions	SDLX_noise_table[] =
{
	{SDLX_NOISE_V1, SDLX_noise_v1_seed, SDLX_noise_v1_next, SDLX_noise_v1_prev, SDLX_noise_v1_add, SDLX_noise_v1_add_into},
};

void	SDLX_load_noise_generator(void)
{
	SDL_assert(SDLX_noise_table[SDLX_NOISE_V1].seed_fn		== SDLX_noise_v1_seed);
	SDL_assert(SDLX_noise_table[SDLX_NOISE_V1].next_fn		== SDLX_noise_v1_next);
	SDL_assert(SDLX_noise_table[SDLX_NOISE_V1].prev_fn		== SDLX_noise_v1_prev);
	SDL_assert(SDLX_noise_table[SDLX_NOISE_V1].add_fn		== SDLX_noise_v1_add);
	SDL_assert(SDLX_noise_table[SDLX_NOISE_V1].add_into_fn	== SDLX_noise_v1_add_into);


	SDL_Log("SDLX Noise Generator(s) Loaded");
}

Uint32	SDLX_noise_next(void *noise_addr, SDLX_noise_version version)
{
	Uint32 result;

	if (version < 0 || version > SDLX_NOISE_VERSION_NULL)
		version = SDLX_NOISE_LATEST;
	result = SDLX_noise_table[version].next_fn(noise_addr);
	return (result);
}

Uint32	SDLX_noise_prev(void *noise_addr, SDLX_noise_version version)
{
	Uint32 result;

	if (version < 0 || version > SDLX_NOISE_VERSION_NULL)
		version = SDLX_NOISE_LATEST;
	result = SDLX_noise_table[version].prev_fn(noise_addr);
	return (result);
}

SDLX_noise	SDLX_noise_seed(Uint32 seed, SDLX_noise_version version)
{
	SDLX_noise result;

	if (version < 0 || version > SDLX_NOISE_VERSION_NULL)
		version = SDLX_NOISE_LATEST;
	result = SDLX_noise_table[version].seed_fn(seed);
	return (result);
}

void	SDLX_noise_add(void *noise_addr, Sint32 by, SDLX_noise_version version)
{
	if (version < 0 || version > SDLX_NOISE_VERSION_NULL)
		version = SDLX_NOISE_LATEST;
	SDLX_noise_table[version].add_fn(noise_addr, by);
}

void	SDLX_noise_add_into(Sint32 *dst, void *noise_addr, Sint32 by, SDLX_noise_version version)
{
	if (version < 0 || version > SDLX_NOISE_VERSION_NULL)
		version = SDLX_NOISE_LATEST;
	SDLX_noise_table[version].add_into_fn(dst, noise_addr, by);
}
