//
// Created by Colin Peppler on 1/5/20.
//

#ifndef SIMPLESQLITE_COMMANDHANDLER_H
#define SIMPLESQLITE_COMMANDHANDLER_H

#include <string.h>

#include "input_buffer.h"
#include "statement.h"
#include "table.h"

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
    PREPARED_STATEMENT_SUCCESS,
    PREPARED_STATEMENT_NEGATIVE_ID,
    PREPARED_STATEMENT_STRING_TOO_LONG,
    PREPARED_STATEMENT_SYNTAX_ERROR,
    PREPARED_STATEMENT_UNRECOGNIZED_STATEMENT
} PreparedStatementResult;

// Executes meta commands
MetaCommandResult execute_meta_command(InputBuffer* input_buffer, Table* table);

// Prepare Insert and Select statements
PreparedStatementResult prepare_statement(InputBuffer* input_buffer, Statement* statement);
PreparedStatementResult prepare_insert(InputBuffer* input_buffer, Statement* statement);

#endif //SIMPLESQLITE_COMMANDHANDLER_H
