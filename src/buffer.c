#include "buffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>


#define BUFFER_START_SIZE 32

uint64_t chkmul(uint64_t a, uint64_t b) {
    if(a == 0 || b == 0) {
        return 0;
    }
    if(UINT_MAX / b < a) {
        return UINT_MAX;
    }
    return a * b;
}

uint64_t chkadd(uint64_t a, uint64_t b) {
    if(UINT_MAX - b < a) {
        return UINT_MAX;
    }
    return a + b;
}

uint64_t chksub(uint64_t a, uint64_t b) {
    if(0 + b > a) {
        return 0;
    }
    return a - b;
}

void init_buffer(fab_buffer_t *buffer) {
    if((buffer->buffer = calloc(sizeof(char), BUFFER_START_SIZE)) == NULL) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    buffer->data_size = 0;
    buffer->buffer_size = BUFFER_START_SIZE;
}

uint64_t append_buffer(fab_buffer_t *buffer, const char *string) {
    uint64_t str_size = strlen(string);
    uint64_t new_size = buffer->buffer_size;
	while(chkadd(str_size, buffer->data_size) >= new_size) {
		new_size = chkmul(new_size, 2);
	}
    if(buffer->buffer_size != new_size) {
        if((buffer->buffer = realloc(buffer->buffer, new_size)) == NULL) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        buffer->buffer_size = new_size;
    }
    memmove(&buffer->buffer[buffer->data_size], string, str_size);
    buffer->data_size = chkadd(buffer->data_size, str_size);
    return buffer->data_size;
}


void truncate_buffer(fab_buffer_t *buffer) {
    uint64_t new_size = chkadd(buffer->data_size, 1);
    if((buffer->buffer = realloc(buffer->buffer, new_size)) == NULL) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    buffer->buffer_size = new_size;
    buffer->buffer[buffer->data_size] = '\0';
}

/**
 * Free the buffer
 * */
void free_buffer(fab_buffer_t *buffer) {
    free(buffer->buffer);
    buffer->buffer = NULL;
    free(buffer);
    buffer = NULL;
}
