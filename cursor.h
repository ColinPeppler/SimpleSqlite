//
// Created by Colin Peppler on 1/16/20.
//

#ifndef SIMPLESQLITE_CURSOR_H
#define SIMPLESQLITE_CURSOR_H

#include <stdint.h>
#include <stdbool.h>

#include "table.h"

typedef struct {
    Table* table;
    uint32_t page_num;      // Page # of the node
    uint32_t cell_num;      // Cell # within node
    bool is_end_of_table;   // Inicates a position one past the last element
} Cursor;

// Create new cursors
Cursor* get_start_table_cursor(Table* table);
Cursor* get_end_table_cursor(Table* table);

// Get the address for a specific table row #
void* cursor_value(Cursor* cursor);

// Increment the number of rows in the table
void cursor_advance(Cursor* cursor);

void leaf_node_insert(Cursor* cursor, uint32_t key, Row* value);

#endif //SIMPLESQLITE_CURSOR_H
