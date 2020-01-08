//
// Created by Colin Peppler on 1/5/20.
//

#ifndef SIMPLESQLITE_STATEMENTEXECUTOR_H
#define SIMPLESQLITE_STATEMENTEXECUTOR_H

#include <stdint.h>

#include "Statement.h"
#include "Table.h"

typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
    EXECUTE_DUPLICATE_KEY,
} ExecuteResult;

// Execute sqlite statements
ExecuteResult execute_statement(Statement* statement, Table* table);
ExecuteResult execute_insert(Statement* statement, Table* table);
ExecuteResult execute_select(Statement* statement, Table* table);


#endif //SIMPLESQLITE_STATEMENTEXECUTOR_H
