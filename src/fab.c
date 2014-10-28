#include "fab.h"
#include <stdlib.h>
#include <stdio.h>


char* make_format(size_t len) {
    size_t esc_size = strlen("\x1b[");
    size_t total_length = (len * 2) + (len - 1) + 2 + esc_size;
    char *format;
    if((format = calloc(sizeof(char), total_length)) == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strncpy(format,"\x1b[", esc_size);
    size_t count = esc_size;
    while(count < total_length-2) {
        format[count] = '%';
        format[count+1] = 'd';
        count += 2;
        if(count < total_length - 3) {
            format[count+2] = ';';
            count++;
        }
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
    vasprintf(&combined, main_format, argptr);
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
        default: return NULL;
    }
    asprintf(&result, "%s%s%s", start, line, end);
    free(start);
    free(end);
    return result;
}
