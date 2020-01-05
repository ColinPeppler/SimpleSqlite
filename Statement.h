//
// Created by Colin Peppler on 1/5/20.
//

#ifndef SIMPLESQLITE_STATEMENT_H
#define SIMPLESQLITE_STATEMENT_H

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct {
    StatementType type;
} Statement;

#endif //SIMPLESQLITE_STATEMENT_H
