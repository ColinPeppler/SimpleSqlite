//
// Created by Colin Peppler on 1/5/20.
//

#include "db.h"

int main(int argc, char* argv[]) {
    InputBuffer* inputBuffer = CreateInputBuffer();

    while (1) {
        printPrompt();
        readInput(inputBuffer);

        if (strcmp(inputBuffer->buffer, ".exit") == 0) {
            closeInputBuffer(inputBuffer);
            exit(1);
        }
        else {
            printf("Unrecognized command '%s'.\n", inputBuffer->buffer);
        }
    }
}
