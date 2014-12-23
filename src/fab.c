#include "fab.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/ioctl.h>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wunknown-attributes"
#pragma clang diagnostic ignored "-Wpadded"
#endif
#include <wand/MagickWand.h>
#ifdef __clang__
#pragma clang diagnostic pop
#endif

#include <math.h>
#include <limits.h>
#include "buffer.h"


/**
 * Interal function and struture definitions
 * j
 * All the xterm <-> RGB stuff is taken from
 * https://github.com/jart/fabulous/blob/master/fabulous/_xterm256.c
 * Thanks to J.A. Roberts Tunney for making this.
 */

#define sqr(x) ((x) * (x))
char *make_format(size_t len);
char *escape(size_t len, ...);
char *colorize(char* start, char* end, const char* line);
int rgb_to_xterm(int r, int g, int b);
int xterm_to_rgb_i(int xcolor);
static int CUBE_STEPS[] = { 0x0, 0x5f, 0x87, 0xAF, 0xD7, 0xFF };
static rgb_t BASIC16[] = { { 0, 0, 0 }, { 205, 0, 0}, { 0, 205, 0 },
    { 205, 205, 0 }, { 0, 0, 238}, { 205, 0, 205 },
    { 0, 205, 205 }, { 229, 229, 229}, { 127, 127, 127 },
    { 255, 0, 0 }, { 0, 255, 0}, { 255, 255, 0 },
    { 92, 92, 255 }, { 255, 0, 255}, { 0, 255, 255 },
    { 255, 255, 255 } };
static bool rgb_init = false;
static rgb_t COLOR_TABLE[256];


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
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-nonliteral"
#endif
    vasprintf(&combined, main_format, argptr);
#ifdef __clang__
#pragma clang diagnostic pop
#endif
    va_end(argptr);
    free(main_format);
    return combined;
}

char *apply_color(Color c, const char *line) {
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
    asprintf(&result, "%s%s%s", start, line, end);
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
    int smallest_distance = INT_MAX;
    int c, d;
    if(rgb_init == false) {
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

char *colorize(char* start, char* end, const char* line) {
    char *result;
    asprintf(&result, "%s%s%s", start, line, end);
    free(start);
    free(end);
    return result;
}

char *foreground_256(rgb_t color, const char *line) {
    int xcolor = rgb_to_xterm(color.r, color.g, color.b);
    return colorize(escape(3, 38, 5, xcolor), escape(1, 39), line);
}

char *background_256(rgb_t color, const char *line) {
    int xcolor = rgb_to_xterm(color.r, color.g, color.b);
    return colorize(escape(3, 48, 5, xcolor), escape(1, 49), line);
}

char *highlight_256(rgb_t color, const char *line) {
    int xcolor = rgb_to_xterm(color.r, color.g, color.b);
    return colorize(escape(4, 38, 5, xcolor, 7), escape(3, 27, 39, 22), line);
}

size_t min(size_t x, size_t y) {
    if(x < y) {
        return x;
    }
    return y;
}

xcolor_image_t *image_to_xterm(const char *path) {
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
    MagickWand *wand;
    MagickBooleanType status;
    MagickPixelPacket pixel;
    PixelIterator *iterator;
    PixelWand **pixels;

    MagickWandGenesis();
    wand = NewMagickWand();
    status = MagickReadImage(wand, path);
    if(status == MagickFalse) {
        exit(EXIT_FAILURE);
    }
    int **xterm_colors = NULL;
    MagickResetIterator(wand);
    size_t row_width = 0;
    size_t im_height = 0;
    size_t im_width = 0;
    size_t width = 0;
    size_t height = 0;
    while(MagickNextImage(wand) != MagickFalse) {
        // Get the actual width and height of the original image
        im_height = MagickGetImageHeight(wand);
        im_width = MagickGetImageWidth(wand);
        // Calculate the new width and height of the image
        width = min(im_width, (size_t) ws.ws_col);
        height = ((im_height * width) / im_width) / 2;
        MagickAdaptiveResizeImage(wand, width, height);

        // iterate through all the pixels
        iterator = NewPixelIterator(wand);
        if((xterm_colors = calloc(height, sizeof(int *))) == NULL) {
            perror("calloc");
            exit(EXIT_FAILURE);
        }

        for(size_t y = 0; y < height; y++) {
            pixels = PixelGetNextIteratorRow(iterator, &row_width);
            if(pixels == (PixelWand **) NULL) {
                break;
            }
            if((xterm_colors[y] = calloc(row_width, sizeof(int))) == NULL) {
                perror("calloc");
                exit(EXIT_FAILURE);
            }
            for(size_t x = 0; x < row_width; x++) {
                PixelGetMagickColor(pixels[x], &pixel);
                int xc = rgb_to_xterm((int)(pixel.red / 255) , (int)(pixel.green / 255), (int)(pixel.blue / 255));
                xterm_colors[y][x] = xc;
            }
        }
        iterator = DestroyPixelIterator(iterator);
        break;
    }
    // We don't need imagemagick anymore, shut it down
    wand = DestroyMagickWand(wand);
    xcolor_image_t *xcolor_image;
    if((xcolor_image = malloc(sizeof(xcolor_image_t))) == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    xcolor_image->x = row_width;
    xcolor_image->y = height;
    xcolor_image->pixels = xterm_colors;
    return xcolor_image;
}

void xcolor_image_free(xcolor_image_t *image) {
    for(size_t y = 0; y < image->y; y++) {
        free(image->pixels[y]);
    }
    free(image->pixels);
    free(image);
    image = NULL;
}

char *image_to_string(const xcolor_image_t *image) {
    fab_buffer_t *buffer;
    if((buffer = malloc(sizeof(fab_buffer_t))) == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    init_buffer(buffer);
    char* start = NULL;
    char* end = escape(1, 49);
    bool open = false;
    for(size_t y = 0; y < image->y; y++) {
        int current_color = 0;
        for(size_t x = 0; x < image->x; x++) {
            if(image->pixels[y][x] != current_color) {
                append_buffer(buffer, end);
                free(start);
                start = escape(3, 48, 5, image->pixels[y][x]);
                append_buffer(buffer, start);
                open = true;
            }
            append_buffer(buffer, " ");
        }
        if(open) {
            append_buffer(buffer, end);
            open = false;
        }
        append_buffer(buffer, "\n");
    }
    truncate_buffer(buffer);
    char *string = buffer->buffer;
    if(start != NULL) {
        free(start);
    }
    free(end);
    free(buffer);
    return string;
}

