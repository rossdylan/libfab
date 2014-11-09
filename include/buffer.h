#ifndef _FAB_BUFFER_H
#define _FAB_BUFFER_H

#include <stdint.h>


typedef struct {
    char *buffer;
    uint64_t data_size;
    uint64_t buffer_size;
} fab_buffer_t;


void init_buffer(fab_buffer_t *buffer);
/**
 * Truncate the empty space in a buffer and turn it into a string
 */
void truncate_buffer(fab_buffer_t *buffer);

/**
 * Append a string to the buffer and return the new size
 * */
uint64_t append_buffer(fab_buffer_t *buffer, const char *string);

/**
 * Free the buffer
 * */
void free_buffer(fab_buffer_t *buffer);
#endif
