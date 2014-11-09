#ifndef _FAB_H
#define _FAB_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "buffer.h"


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

typedef struct {
    int y;
    int x;
    int **pixels;
} xcolor_image_t;

char *apply_color(Color c, const char *line);

char *foreground_256(rgb_t color, const char *line);
char *background_256(rgb_t color, const char *line);
char *highlight_256(rgb_t color, const char *line);

size_t min(size_t x, size_t y);
xcolor_image_t *image_to_xterm(char *path);
fab_buffer_t *reduce_image(xcolor_image_t *image);
void xcolor_image_free(xcolor_image_t *image);
#endif
