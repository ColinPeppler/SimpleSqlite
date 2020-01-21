//
// Created by Colin Peppler on 1/16/20.
//

#ifndef SIMPLESQLITE_CURSOR_H
#define SIMPLESQLITE_CURSOR_H

#include <stdint.h>
#include <stdbool.h>

#include "table.h"

typedef struct {
    Table *table;
    uint32_t page_num;      // Page # of the node
    uint32_t cell_num;      // Cell # within node
    bool is_end_of_table;   // Inicates a position one past the last element
} Cursor;

// Create new cursors
Cursor *get_start_table_cursor(Table *table);

// Find cursor for a table @ an index
Cursor *table_find(Table *table, uint32_t key);

// Get the address for a specific table row #
void *cursor_value(Cursor *cursor);

// Increment the number of rows in the table
void cursor_advance(Cursor *cursor);

// Inserting a leaf node into table
void leaf_node_insert(Cursor *cursor, uint32_t key, Row *value);

void leaf_node_split_and_insert(Cursor *cursor, uint32_t key, Row *value);

// Finding a value within a leaf node or internal node
Cursor *leaf_node_find(Table *table, uint32_t page_num, uint32_t target_key);

Cursor *internal_node_find(Table *table, uint32_t page_num, uint32_t target_key);

// Helper
uint32_t internal_node_find_child(void *node, uint32_t target_key);


#endif //SIMPLESQLITE_CURSOR_H
