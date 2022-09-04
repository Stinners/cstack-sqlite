
#include <stdio.h>
#include <stdlib.h>

#include "input_buffer.h"

InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void print_prompt() { printf("db > "); }

void read_input(InputBuffer* buf) {
    ssize_t bytes_read = getline(&(buf->buffer), &(buf->buffer_length), stdin);

    if (bytes_read <= 0) {
        printf("Error reading input: Exiting\n");
        exit(EXIT_FAILURE);
    }

    // Truncate the endline 
    buf->input_length = bytes_read - 1;
    buf->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* buf) {
    free(buf->buffer);
    free(buf);
}
