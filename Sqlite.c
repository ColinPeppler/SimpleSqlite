//
// Created by Colin Peppler on 1/5/20.
//

#include "Sqlite.h"

int main(int argc, char* argv[]) {
    InputBuffer *input_buffer = create_input_buffer();

    while(1) {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.') {
            switch (execute_meta_command(input_buffer)) {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch(prepare_statement(input_buffer, &statement)) {
            case(PREPARED_STATEMENT_SUCCESS):
                break;
            case (PREPARED_STATEMENT_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
                continue;
        }

        ExecuteStatement(&statement);
        printf("Executed.\n");
    }
}
