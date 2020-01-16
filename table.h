//
// Created by Colin Peppler on 1/7/20.
//

#ifndef SIMPLESQLITE_TABLE_H
#define SIMPLESQLITE_TABLE_H

#include <stdlib.h>
#include <stdint.h>
#include <zconf.h>
#include <stdio.h>

#include "memory_manager.h"
#include "pager.h"

static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

typedef struct {
    Pager *pager;
    uint32_t root_page_num;
} Table;

#include "BTreeNode.h"

// Table constructor
Table *db_open(const char *filename);

// Free the table
Table *free_table();

Table *db_close(Table *table);

void print_row(Row *row);

#endif //SIMPLESQLITE_TABLE_H
