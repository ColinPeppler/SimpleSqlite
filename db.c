//
// Created by Colin Peppler on 1/5/20.
//

#include "db.h"

int main(int argc, char* argv[]) {
    InputBuffer *inputBuffer = CreateInputBuffer();

    while(1) {
        printPrompt();
        readInput(inputBuffer);

        if (inputBuffer->buffer[0] == '.') {
            switch (ExecuteMetaCommand(inputBuffer)) {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'\n", inputBuffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch(PrepareStatement(inputBuffer, &statement)) {
            case(PREPARED_STATEMENT_SUCCESS):
                break;
            case (PREPARED_STATEMENT_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start of '%s'.\n", inputBuffer->buffer);
                continue;
        }

        ExecuteStatement(&statement);
        printf("Executed.\n");
    }
}
