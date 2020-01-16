//
// Created by Colin Peppler on 1/5/20.
//

#include "statement_executor.h"

ExecuteResult execute_statement(Statement *statement, Table *table) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            return execute_insert(statement, table);
        case (STATEMENT_SELECT):
            return execute_select(statement, table);
    }
}

ExecuteResult execute_insert(Statement *statement, Table *table) {
    void* node = get_page(table->pager, table->root_page_num);
    if ((*leaf_node_num_cells(node)) >= LEAF_NODE_MAX_CELLS) {
        return EXECUTE_TABLE_FULL;
    }

    Row *row_to_insert = &(statement->row_to_insert);
    Cursor* cursor = get_end_table_cursor(table);

    leaf_node_insert(cursor, row_to_insert->id, row_to_insert);

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement *statement, Table *table) {
    Cursor* cursor = get_start_table_cursor(table);
    Row row;

    while (!cursor->is_end_of_table) {
        deserialize_row(cursor_value(cursor), &row);
        print_row(&row);
        cursor_advance(cursor);
    }
    free(cursor);

    return EXECUTE_SUCCESS;
}
