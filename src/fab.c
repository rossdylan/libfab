#include "fab.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


char* make_format(size_t len) {
    size_t esc_size = strlen("\x1b[");
    size_t total_length = (len * 2) + (len - 1) + 2 + esc_size;
    size_t count = esc_size;
    char *format;
    if((format = calloc(sizeof(char), total_length)) == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strncpy(format,"\x1b[", esc_size);
    while(count < total_length-2) {
        format[count] = '%';
        format[count+1] = 'd';
        if(count < total_length - 3) {
            format[count+2] = ';';
            count += 1;
        }
        count += 2;
    }
    format[total_length-2] = 'm';
    format[total_length-1] = '\0';
    return format;
}

char *escape(size_t len, ...) {
    char* main_format = make_format(len);
    char* combined;
    va_list argptr;
    va_start(argptr, len);
    if(vasprintf(&combined, main_format, argptr)){};
    va_end(argptr);
    free(main_format);
    return combined;
}

char *apply_format(Color c, char *line) {
    char *result;
    char *start;
    char *end;
    switch(c) {
        case BOLD:
            start = escape(1, 1);
            end = escape(1, 22);
            break;
        case ITALIC:
            start = escape(1, 3);
            end = escape(1, 23);
            break;
        case UNDER:
            start = escape(1, 4);
            end = escape(1, 24);
            break;
        case UNDER2:
            start = escape(1, 21);
            end = escape(1, 24);
            break;
        case STRIKE:
            start = escape(1, 9);
            end = escape(1, 29);
            break;
        case BLINK:
            start = escape(1, 5);
            end = escape(1, 25);
            break;
        case FLIP:
            start = escape(1, 7);
            end = escape(1, 27);
            break;
        case BLACK:
            start = escape(1, 30);
            end = escape(1, 39);
            break;
        case RED:
            start = escape(1, 31);
            end = escape(1, 39);
            break;
        case GREEN:
            start = escape(1, 32);
            end = escape(1, 39);
            break;
        case YELLOW:
            start = escape(1, 33);
            end = escape(1, 39);
            break;
        case BLUE:
            start = escape(1, 34);
            end = escape(1, 39);
            break;
        case MAGENTA:
            start = escape(1, 35);
            end = escape(1, 39);
            break;
        case CYAN:
            start = escape(1, 36);
            end = escape(1, 39);
            break;
        case WHITE:
            start = escape(1, 37);
            end = escape(1, 39);
            break;
        case HBLACK:
            start = escape(3, 1, 30, 7);
            end = escape(3, 22, 27, 39);
            break;
        case HRED:
            start = escape(3, 1, 31, 7);
            end = escape(3, 22, 27, 39);
            break;
        case HGREEN:
            start = escape(3, 1, 32, 7);
            end = escape(3, 22, 27, 39);
            break;
        case HYELLOW:
            start = escape(3, 1, 33, 7);
            end = escape(3, 22, 27, 39);
            break;
        case HBLUE:
            start = escape(3, 1, 34, 7);
            end = escape(3, 22, 27, 39);
            break;
        case HMAGENTA:
            start = escape(3, 1, 35, 7);
            end = escape(3, 22, 27, 39);
            break;
        case HCYAN:
            start = escape(3, 1, 36, 7);
            end = escape(3, 22, 27, 39);
            break;
        case HWHITE:
            start = escape(3, 1, 37, 7);
            end = escape(3, 22, 27, 39);
            break;
        case BGBLACK:
            start = escape(1, 40);
            end = escape(1, 49);
            break;
        case BGRED:
            start = escape(1, 41);
            end = escape(1, 49);
            break;
        case BGGREEN:
            start = escape(1, 42);
            end = escape(1, 49);
            break;
        case BGYELLOW:
            start = escape(1, 43);
            end = escape(1, 49);
            break;
        case BGBLUE:
            start = escape(1, 44);
            end = escape(1, 49);
            break;
        case BGMAGENTA:
            start = escape(1, 45);
            end = escape(1, 49);
            break;
        case BGCYAN:
            start = escape(1, 46);
            end = escape(1, 49);
            break;
        case BGWHITE:
            start = escape(1, 47);
            end = escape(1, 49);
            break;
    }
    if(asprintf(&result, "%s%s%s", start, line, end)){};
    free(start);
    free(end);
    return result;
}

rgb_t xterm_to_rgb(int xcolor) {
    rgb_t res;
    if (xcolor < 16) {
        res = BASIC16[xcolor];
    } else if (16 <= xcolor && xcolor <= 231) {
        xcolor -= 16;
        res.r = CUBE_STEPS[(xcolor / 36) % 6];
        res.g = CUBE_STEPS[(xcolor / 6) % 6];
        res.b = CUBE_STEPS[xcolor % 6];
    } else if (232 <= xcolor && xcolor <= 255) {
        res.r = res.g = res.b = 8 + (xcolor - 232) * 0x0A;
    }
    return res;
}


/**
 * * This function provides a quick and dirty way to serialize an rgb_t
 * * struct to an int which can be decoded by our Python code using
 * * ctypes.
 * */
int xterm_to_rgb_i(int xcolor)
{
    rgb_t res = xterm_to_rgb(xcolor);
    return (res.r << 16) | (res.g << 8) | (res.b << 0);
}


/**
 * * Quantize RGB values to an xterm 256-color ID
 * */
int rgb_to_xterm(int r, int g, int b)
{
    int best_match = 0;
    int smallest_distance = 1000000000;
    int c, d;
    if(rgb_init == false) {
       int c;
       for (c = 0; c < 256; c++) {
           COLOR_TABLE[c] = xterm_to_rgb(c);
       }
       rgb_init = true;
    }
    for (c = 16; c < 256; c++) {
        d = sqr(COLOR_TABLE[c].r - r) +
            sqr(COLOR_TABLE[c].g - g) +
            sqr(COLOR_TABLE[c].b - b);
        if (d < smallest_distance) {
            smallest_distance = d;
            best_match = c;
        }
    }
    return best_match;
}

char *colorize(char* start, char* end, char* line) {
    char *result;
    if(asprintf(&result, "%s%s%s", start, line, end)){};
    free(start);
    free(end);
    return result;
}

char *foreground_256(rgb_t color, char *line) {
    int xcolor = rgb_to_xterm(color.r, color.g, color.b);
    return colorize(escape(3, 38, 5, xcolor), escape(1, 39), line);
}

char *background_256(rgb_t color, char *line) {
    int xcolor = rgb_to_xterm(color.r, color.g, color.b);
    return colorize(escape(3, 48, 5, xcolor), escape(1, 49), line);
}

char *highlight_256(rgb_t color, char *line) {
    int xcolor = rgb_to_xterm(color.r, color.g, color.b);
    return colorize(escape(4, 38, 5, xcolor, 7), escape(3, 27, 39, 22), line);
}
