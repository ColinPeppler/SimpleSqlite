//
// Created by Colin Peppler on 1/7/20.
//

#ifndef SIMPLESQLITE_TABLE_H
#define SIMPLESQLITE_TABLE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "memory_manager.h"

# define TABLE_MAX_PAGES 100

static const uint32_t PAGE_SIZE = 4096;
static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

typedef struct {
    uint32_t num_rows;
    void* pages[TABLE_MAX_PAGES];
} Table;

// Table constructor
Table* new_table();

// Free the table
Table* free_table();

// Get the address for a specific table row #
void* find_row_address(Table* table, uint32_t row_num);

// Print a row
void print_row(Row* row);

#endif //SIMPLESQLITE_TABLE_H
