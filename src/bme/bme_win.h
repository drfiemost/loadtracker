// BME windows, input & timing module header file

#ifndef BME_WIN_H
#define BME_WIN_H

#include <SDL3/SDL.h>

constexpr int MAX_COLORS = 16;

constexpr int MAX_COLUMNS = 128;
constexpr int MAX_ROWS    =  40;

enum
{
  MOUSEB_LEFT   = 1,
  MOUSEB_RIGHT  = 2,
  MOUSEB_MIDDLE = 4
};

bool win_openwindow(const char *appname);
void win_closewindow();
void win_seticon(char *iconbuffer, int size);
int win_getspeed(int framerate);

bool gfx_init(unsigned xsize, unsigned ysize);
void gfx_uninit();
bool gfx_lock();
void gfx_unlock();
void gfx_flip();

void gfx_setpalette();

bool gfx_loadcursor(const char *name);
void gfx_drawcursor(int x, int y);
void gfx_freecursor();

bool gfx_loadcharset(const char *name, unsigned char *chardata);

void mou_getpos(unsigned *x, unsigned *y);
unsigned mou_getbuttons();

int key_get();
int key_getraw();
bool key_shift();
bool key_alt();

extern bool win_quitted;
extern int win_fullscreen;
extern float win_mouseywheel;

extern bool gfx_redraw;
extern unsigned char gfx_palette[];
extern SDL_Surface *gfx_screen;

extern unsigned xpos;
extern unsigned ypos;
extern unsigned xsize;
extern unsigned ysize;

#endif
