//
// Created by Colin Peppler on 1/16/20.
//

#include "cursor.h"

Cursor* get_start_table_cursor(Table* table) {
    Cursor* cursor = malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->page_num = table->root_page_num;
    cursor->cell_num = 0;

    void* root_node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = *leaf_node_num_cells(root_node);
    cursor->is_end_of_table = (num_cells == 0);

    return cursor;
}

Cursor* get_end_table_cursor(Table* table) {
    Cursor* cursor = malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->page_num = table->root_page_num;
    cursor->is_end_of_table = true;

    void* root_node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = *leaf_node_num_cells(root_node);
    cursor->cell_num = num_cells;

    return cursor;
}

void* cursor_value(Cursor* cursor) {
    uint32_t page_num = cursor->page_num;
    void *page = get_page(cursor->table->pager, page_num);

    return leaf_node_value(page, cursor->cell_num);
}

void cursor_advance(Cursor* cursor){
    uint32_t page_num = cursor->page_num;
    void* node = get_page(cursor->table->pager, page_num);

    cursor->cell_num += 1;
    if (cursor->cell_num >= (*leaf_node_num_cells(node))) {
        cursor->is_end_of_table = true;
    }
}
