#ifndef _FAB_H
#define _FAB_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#define sqr(x) ((x) * (x))

#include <stdint.h>
#include <string.h>
#include <stdbool.h>


typedef enum {
    BOLD,
    ITALIC,
    UNDER,
    UNDER2,
    STRIKE,
    BLINK,
    FLIP,
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    HBLACK,
    HRED,
    HGREEN,
    HYELLOW,
    HBLUE,
    HMAGENTA,
    HCYAN,
    HWHITE,
    BGBLACK,
    BGRED,
    BGGREEN,
    BGYELLOW,
    BGBLUE,
    BGMAGENTA,
    BGCYAN,
    BGWHITE
} Color;

/*
 * All the xterm <-> RGB stuff is taken from
 * https://github.com/jart/fabulous/blob/master/fabulous/_xterm256.c
 * Thanks to J.A. Roberts Tunney for making this.
 */
typedef struct {
    int r;
    int g;
    int b;
} rgb_t;

static int CUBE_STEPS[] = { 0x0, 0x5f, 0x87, 0xAF, 0xD7, 0xFF };

static rgb_t BASIC16[] = { { 0, 0, 0 }, { 205, 0, 0}, { 0, 205, 0 },
    { 205, 205, 0 }, { 0, 0, 238}, { 205, 0, 205 },
    { 0, 205, 205 }, { 229, 229, 229}, { 127, 127, 127 },
    { 255, 0, 0 }, { 0, 255, 0}, { 255, 255, 0 },
    { 92, 92, 255 }, { 255, 0, 255}, { 0, 255, 255 },
    { 255, 255, 255 } };

static bool rgb_init = false;
static rgb_t COLOR_TABLE[256];

rgb_t xterm_to_rgb(int xcolor);
int xterm_to_rgb_i(int xcolor);
int rgb_to_xterm(int r, int g, int b);

char *make_format(size_t len);
void free_format(char *format);

char *apply_format(Color c, char *line);
char *escape(size_t len, ...);
char *colorize(char *start, char *end, char *line);

char *foreground_256(rgb_t color, char *line);
char *background_256(rgb_t color, char *line);
char *complement_256(rgb_t color, char *lines);
char *highlight_256(rgb_t color, char *line);
#endif
