//
// Created by Colin Peppler on 1/5/20.
//

#include "command_handler.h"


MetaCommandResult execute_meta_command(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    }
    else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PreparedStatementResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        int args_assigned = sscanf(input_buffer->buffer, "insert %d %s %s", &(statement->row_to_insert.id),
                                   statement->row_to_insert.username, statement->row_to_insert.email);
        if (args_assigned != NUM_ARGS) {
            return PREPARED_STATEMENT_SYNTAX_ERROR;
        }
        return PREPARED_STATEMENT_SUCCESS;
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARED_STATEMENT_SUCCESS;
    }

    return PREPARED_STATEMENT_UNRECOGNIZED_STATEMENT;
}
