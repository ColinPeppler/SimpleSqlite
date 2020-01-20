//
// Created by Colin Peppler on 1/16/20.
//

#include "BTreeNode.h"

uint32_t* leaf_node_num_cells(void* node) {
    return node + LEAF_NODE_NUM_CELLS_OFFSET;
}

void* leaf_node_cell(void* node, uint32_t cell_num) {
    return node + LEAF_NODE_HEADER_SIZE + cell_num * LEAF_NODE_CELL_SIZE;
}

uint32_t* leaf_node_key(void* node, uint32_t cell_num) {
    return leaf_node_cell(node, cell_num);
}

void* leaf_node_value(void* node, uint32_t cell_num) {
    return leaf_node_cell(node, cell_num) + LEAF_NODE_KEY_SIZE;
}

void initialize_leaf_node(void* node) {
    set_node_type(node, NODE_LEAF);
    *leaf_node_num_cells(node) = 0;
}

void leaf_node_insert(Cursor* cursor, uint32_t key, Row* value){
    void* node = get_page(cursor->table->pager, cursor->page_num);

    uint32_t num_cells = *leaf_node_num_cells(node);

    // Node full
    if (num_cells >= LEAF_NODE_MAX_CELLS) {
        printf("Need to implement splitting a leaf node.\n");
        exit(EXIT_FAILURE);
    }

    // Make room for new cell
    if (cursor->cell_num < num_cells) {
        for (uint32_t i = num_cells; i > cursor->cell_num; i--) {
            memcpy(leaf_node_cell(node, i), leaf_node_cell(node, i-1), LEAF_NODE_CELL_SIZE);
        }
    }

    // Increment # of cells and place key and value into memory
    *(leaf_node_num_cells(node)) += 1;
    *(leaf_node_key(node, cursor->cell_num)) = key;
    serialize_row(value, leaf_node_value(node, cursor->cell_num));
}

Cursor* leaf_node_find(Table* table, uint32_t page_num, uint32_t target_key) {
    void* node = get_page(table->pager, page_num);

    Cursor* cursor = malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->page_num = page_num;
//    cursor->is_end_of_table = false;

    uint32_t index = binary_search(node, target_key);
    cursor->cell_num = index;
    return cursor;
}

uint32_t binary_search(void* node, uint32_t target_key) {
    uint32_t num_cells = *leaf_node_num_cells(node);
    uint32_t lo = 0;
    uint32_t hi = num_cells;
    while (lo < hi) {
        uint32_t index = (uint32_t)(lo + hi) >> 1;
        uint32_t key = *leaf_node_key(node, index);

        if (key == target_key) {
            return index;
        }
        else if (key < target_key) {
            hi = index;
        }
        else {
            lo = index + 1;
        }
    }

    return lo;
}

BTreeNodeType get_node_type(void* node) {
    uint8_t value = *(uint8_t*)(node + NODE_TYPE_OFFSET);
    return (BTreeNodeType)value;
}

void set_node_type(void* node, BTreeNodeType type){
    uint8_t value = type;
    *(uint8_t*)(node + NODE_TYPE_OFFSET) = value;
}
