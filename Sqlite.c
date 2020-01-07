//
// Created by Colin Peppler on 1/5/20.
//

#include "Sqlite.h"

int main(int argc, char* argv[]) {
    InputBuffer *inputBuffer = create_input_buffer();

    while(1) {
        print_prompt();
        read_input(inputBuffer);

        if (inputBuffer->buffer[0] == '.') {
            switch (execute_meta_command(inputBuffer)) {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'\n", inputBuffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch(prepare_statement(inputBuffer, &statement)) {
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
