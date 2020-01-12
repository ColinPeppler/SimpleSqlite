//
// Created by Colin Peppler on 1/5/20.
//

#include <stdlib.h>
#include <stdio.h>

#ifndef SQLITE_INPUTBUFFER_H
#define SQLITE_INPUTBUFFER_H

typedef struct {
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

// Constructor
InputBuffer *create_input_buffer();

// Prints a prompt to the user
void print_prompt();

// Reads a line of the user's input
void read_input(InputBuffer *input_buffer);

// Free the InputBuffer
void close_input_buffer(InputBuffer *input_buffer);

#endif //SQLITE_INPUTBUFFER_H
