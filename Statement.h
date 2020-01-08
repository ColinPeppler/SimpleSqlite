//
// Created by Colin Peppler on 1/5/20.
//

#ifndef SIMPLESQLITE_STATEMENT_H
#define SIMPLESQLITE_STATEMENT_H

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

typedef struct {
    StatementType type;
    Row row_to_insert;      // to be used by insert statements
} Statement;

// Convert a Row struct to a compact memory segment
void serialize_row(Row* source, void* destination);

// Convert from a compact memory segment to a Row struct
void deserialize_row(void* source, Row* destination);

#endif //SIMPLESQLITE_STATEMENT_H
