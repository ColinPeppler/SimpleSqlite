//
// Created by Colin Peppler on 1/16/20.
//

#include "BTree.h"

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
    set_node_root(node, false);
}

void initialize_internal_node(void* node) {
    set_node_type(node, NODE_INTERNAL);
    set_node_root(node, false);
    *internal_node_num_keys(node) = 0;
}

void leaf_node_insert(Cursor* cursor, uint32_t key, Row* value){
    void* node = get_page(cursor->table->pager, cursor->page_num);

    uint32_t num_cells = *leaf_node_num_cells(node);

    // Node full
    if (num_cells >= LEAF_NODE_MAX_CELLS) {
        leaf_node_split_and_insert(cursor, key, value);
        return;
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

void leaf_node_split_and_insert(Cursor* cursor, uint32_t key, Row* value) {
    // Create a new node
    void* old_node = get_page(cursor->table->pager, cursor->page_num);
    uint32_t new_page_num = get_unused_page_num(cursor->table->pager);
    void* new_node = get_page(cursor->table->pager, new_page_num);
    initialize_leaf_node(new_node);

    // Copy each cell to its new location
    for (int32_t i = LEAF_NODE_MAX_CELLS; i >= 0; i--) {
        void* destination_node;
        if (i >= LEAF_NODE_LEFT_SPLIT_COUNT) {
            destination_node = new_node;
        } else {
            destination_node = old_node;
        }

        uint32_t index_within_node = i % LEAF_NODE_LEFT_SPLIT_COUNT;
        void* destination = leaf_node_cell(destination_node, index_within_node);

        if (i == cursor->cell_num) {
            void *destination_value = leaf_node_value(destination_node, index_within_node);
            serialize_row(value, destination_value);
            *leaf_node_key(destination_node, index_within_node) = key;
        }
        else {
            uint32_t original_index = (i > cursor->cell_num) ? i-1 : i;
            void* original_cell = leaf_node_cell(old_node, original_index);
            memcpy(destination, original_cell, LEAF_NODE_CELL_SIZE);
        }
    }

    // Update cell counts on both leaf nodes
    *leaf_node_num_cells(old_node) = LEAF_NODE_LEFT_SPLIT_COUNT;
    *leaf_node_num_cells(new_node) = LEAF_NODE_RIGHT_SPLIT_COUNT;

    // Update root node or parent
    if (is_node_root(old_node)) {
        return create_new_root(cursor->table, new_page_num);
    }
    else {
        printf("TODO: implement updating parent after split");
        exit(EXIT_FAILURE);
    }
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

void create_new_root(Table* table, uint32_t right_child_page_num) {
    /**
     1. Move lower half of root to left child
     2. Move upper half of root to right child
     3. Set root's only key to the max in left child
    **/

    void* root = get_page(table->pager, table->root_page_num);
    void* right_child = get_page(table->pager, right_child_page_num);
    uint32_t left_child_page_num = get_unused_page_num(table->pager);
    void* left_child = get_page(table->pager, left_child_page_num);

    // Copy old root data to left child
    memcpy(left_child, root, PAGE_SIZE);
    set_node_root(left_child, false);

    // Update root node
    initialize_internal_node(root);
    set_node_root(root, true);
    *internal_node_num_keys(root) = 1;
    *internal_node_child(root, 0) = left_child_page_num;
    uint32_t left_child_max_key = get_node_max_key(left_child);
    *internal_node_key(root, 0) = left_child_max_key;
    *internal_node_right_child(root) = right_child_page_num;
    *node_parent(left_child) = table->root_page_num;
    *node_parent(right_child) = table->root_page_num;
}

uint32_t* internal_node_num_keys(void* node) {
    return node + INTERNAL_NODE_NUM_KEYS_OFFSET;
}

uint32_t* internal_node_right_child(void* node) {
    return node + INTERNAL_NODE_RIGHT_CHILD_OFFSET;
}

uint32_t* internal_node_cell(void* node, uint32_t cell_num) {
   return node + INTERNAL_NODE_HEADER_SIZE + cell_num * INTERNAL_NODE_CELL_SIZE;
}

uint32_t* internal_node_child(void* node, uint32_t child_num) {
   uint32_t num_keys = *internal_node_num_keys(node);
   if (child_num > num_keys) {
       printf("Tried to access child_num %d > num_keys %d\n", child_num, num_keys);
       exit(EXIT_FAILURE);
   }
   else if (child_num == num_keys) {
       return internal_node_right_child(node);
   }
   else {
       return internal_node_cell(node, child_num);
   }
}

uint32_t* internal_node_key(void* node, uint32_t key_num) {
    return internal_node_cell(node, key_num) + INTERNAL_NODE_CHILD_SIZE;
}

bool is_node_root(void* node) {
    uint8_t value = *(uint8_t*)(node + IS_ROOT_OFFSET);
    return (bool)value;
}

void set_node_root(void* node, bool is_root) {
    uint8_t value = is_root;
    *(uint8_t*)(node + IS_ROOT_OFFSET) = value;
}


uint32_t get_node_max_key(void *node) {
    switch (get_node_type(node)) {
        case NODE_INTERNAL:
            return *internal_node_key(node, *internal_node_num_keys(node) - 1);
        case NODE_LEAF:
            return *leaf_node_key(node, *leaf_node_num_cells(node) - 1);
    }
}

uint32_t* node_parent(void* node) {
    return node + PARENT_POINTER_OFFSET;
}

void indent(uint32_t level) {
    for (uint32_t i = 0; i < level; i++) {
        printf(" ");
    }
}

void print_tree(Pager* pager, uint32_t page_num, uint32_t indentation_level) {
    void* node = get_page(pager, page_num);
    uint32_t num_keys, child;

    switch (get_node_type(node)) {
        case (NODE_LEAF):
            num_keys = *leaf_node_num_cells(node);
            indent(indentation_level);
            printf("- leaf (size %d)\n", num_keys);
            for (uint32_t i = 0; i < num_keys; i++) {
                indent(indentation_level + 1);
                printf("- %d\n", *leaf_node_key(node, i));
            }
            break;
        case (NODE_INTERNAL):
            num_keys = *internal_node_num_keys(node);
            indent(indentation_level);
            printf("- internal (side %d)\n", num_keys);
            for (uint32_t i = 0; i < num_keys; i++) {
                child + *internal_node_child(node, i);
                print_tree(pager, child, indentation_level + 1);

                indent(indentation_level + 1);
                printf("- key %d\n", *internal_node_key(node, i));
            }
            child = *internal_node_right_child(node);
            print_tree(pager, child, indentation_level + 1);
            break;
    }
}
