#ifndef _FAB_H
#define _FAB_H
#define _GNU_SOURCE
#include <stdint.h>
#include <string.h>


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


char *make_format(size_t len);
void free_format(char *format);

char *apply_format(Color c, char *line);
char *escape(size_t len, ...);
#endif
