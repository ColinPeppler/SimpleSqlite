//
// Created by Colin Peppler on 1/16/20.
//

#include "cursor.h"

Cursor* get_start_table_cursor(Table* table) {
    Cursor* cursor = table_find(table, 0);

    void* node = get_page(table->pager, cursor->page_num);
    uint32_t num_cells = *leaf_node_num_cells(node);
    cursor->is_end_of_table = (num_cells == 0);

    return cursor;
}

Cursor* table_find(Table* table, uint32_t key) {
    uint32_t root_page_num = table->root_page_num;
    void* root_node = get_page(table->pager, root_page_num);

    switch (get_node_type(root_node)) {
        case (NODE_LEAF):
            return leaf_node_find(table, root_page_num, key);
        default:
            return internal_node_find(table, root_page_num, key);
    }
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
        // Advanced to the next leaf node if there is one
        uint32_t next_page_num = *leaf_node_next_leaf(node);
        if (next_page_num == 0) {
            cursor->is_end_of_table = true;

        } else {
            cursor->page_num = next_page_num;
            cursor->cell_num = 0;
        }
    }
}
