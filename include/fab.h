#ifndef _FAB_H
#define _FAB_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

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

typedef struct {
    int r;
    int g;
    int b;
} rgb_t;


rgb_t xterm_to_rgb(int xcolor);
int xterm_to_rgb_i(int xcolor);
int rgb_to_xterm(int r, int g, int b);

char *make_format(size_t len);

char *apply_format(Color c, const char *line);
char *escape(size_t len, ...);
char *colorize(char *start, char *end, const char *line);

char *foreground_256(rgb_t color, const char *line);
char *background_256(rgb_t color, const char *line);
char *highlight_256(rgb_t color, const char *line);
#endif
