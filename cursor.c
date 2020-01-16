//
// Created by Colin Peppler on 1/16/20.
//

#include "cursor.h"

Cursor* get_start_table_cursor(Table* table) {
    Cursor* cursor = malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->row_num = 0;
    cursor->is_end_of_table = (table->num_rows == 0);

    return cursor;
}

Cursor* get_end_table_cursor(Table* table) {
    Cursor* cursor = malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->row_num = table->num_rows;
    cursor->is_end_of_table = true;

    return cursor;
}

void* cursor_value(Cursor* cursor) {
    uint32_t row_num = cursor->row_num;
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void *page = get_page(cursor->table->pager, page_num);
    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;

    return page + byte_offset;
}

void cursor_advance(Cursor* cursor){
    cursor->row_num += 1;
    if (cursor->row_num >= cursor->table->num_rows) {
        cursor->is_end_of_table = true;
    }
}
