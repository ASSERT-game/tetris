#ifndef SDLX_CONFIG_H
#define SDLX_CONFIG_H

#ifdef EMCC
#define DISPLAY_SCALE (4)
#else
#define DISPLAY_SCALE (2)
#endif

#define WIN_TITLE "Tetris"
#define WIN_WIDTH (304 * DISPLAY_SCALE)
#define WIN_HEIGHT (450 * DISPLAY_SCALE)
#define WIN_POS_X (2300)
#define WIN_POS_Y (100)

#endif
