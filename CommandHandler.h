//
// Created by Colin Peppler on 1/5/20.
//

#include <string.h>

#include "InputBuffer.h"
#include "Statement.h"

#ifndef SIMPLESQLITE_COMMANDHANDLER_H
#define SIMPLESQLITE_COMMANDHANDLER_H

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
MetaCommandResult ExecuteMetaCommand(InputBuffer* inputBuffer);

// Prepare Insert and Select statements
PreparedStatementResult PrepareStatement(InputBuffer* inputBuffer, Statement* statement);

#endif //SIMPLESQLITE_COMMANDHANDLER_H