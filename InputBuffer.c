//
// Created by Colin Peppler on 1/5/20.

//

#include "InputBuffer.h"

InputBuffer* CreateInputBuffer() {
    InputBuffer* inputBuffer = malloc(sizeof(InputBuffer));
    inputBuffer->buffer = NULL;
    inputBuffer->bufferLength = 0;
    inputBuffer->inputLength = 0;

    return inputBuffer;
}

void printPrompt() { printf("db > "); }

void readInput(InputBuffer* inputBuffer) {
    ssize_t bytesRead = getline(&(inputBuffer->buffer), &(inputBuffer->bufferLength), stdin);

    if (bytesRead <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // Ignore trailing newline '\n'
    inputBuffer->inputLength = bytesRead - 1;
    inputBuffer->buffer[bytesRead - 1] = '\0';
}

void closeInputBuffer(InputBuffer* inputBuffer) {
    free(inputBuffer->buffer);
    free(inputBuffer);
}
