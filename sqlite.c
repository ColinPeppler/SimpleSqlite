//
// Created by Colin Peppler on 1/5/20.
//

#include "sqlite.h"

int main(int argc, char *argv[]) {
    if (argc < NUM_ARGS) {
        printf("Must supple a database filename,\n");
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    Table *table = db_open(filename);
    InputBuffer *input_buffer = create_input_buffer();

    while (1) {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.') {
            switch (execute_meta_command(input_buffer, table)) {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case (PREPARED_STATEMENT_SUCCESS):
                break;
            case (PREPARED_STATEMENT_NEGATIVE_ID):
                printf("ID must be positive.\n");
                continue;
            case (PREPARED_STATEMENT_STRING_TOO_LONG):
                printf("String is too long.\n");
                continue;
            case (PREPARED_STATEMENT_SYNTAX_ERROR):
                printf("Syntax error. Could not parse statement. (%s)\n", input_buffer->buffer);
                continue;
            case (PREPARED_STATEMENT_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
                continue;
        }

        switch (execute_statement(&statement, table)) {
            case (EXECUTE_SUCCESS):
                printf("Executed.\n");
                break;
            case (EXECUTE_TABLE_FULL):
                printf("Error: Table full.\n");
                break;
        }
    }
}
