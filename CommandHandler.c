//
// Created by Colin Peppler on 1/5/20.
//

#include "CommandHandler.h"


MetaCommandResult execute_meta_command(InputBuffer* inputBuffer) {
    if (strcmp(inputBuffer->buffer, ".exit") == 0) {
        close_input_buffer(inputBuffer);
        exit(EXIT_SUCCESS);
    }
    else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PreparedStatementResult prepare_statement(InputBuffer* inputBuffer, Statement* statement) {
    if (strncmp(inputBuffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARED_STATEMENT_SUCCESS;
    }
    if (strcmp(inputBuffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARED_STATEMENT_SUCCESS;
    }

    return PREPARED_STATEMENT_UNRECOGNIZED_STATEMENT;
}
