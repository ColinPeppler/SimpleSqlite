//
// Created by Colin Peppler on 1/8/20.
//

#ifndef SIMPLESQLITE_MEMORY_MANAGER_H
#define SIMPLESQLITE_MEMORY_MANAGER_H

#include <stdint.h>
#include <string.h>

#include "statement.h"

// macro to define size of a struct's attribute
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

static const uint32_t ID_SIZE = size_of_attribute(Row, id);
static const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
static const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
static const uint32_t ID_OFFSET = 0;
static const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
static const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
static const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

// Convert a row to and from a compact memory segment
void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);

#endif //SIMPLESQLITE_MEMORY_MANAGER_H
