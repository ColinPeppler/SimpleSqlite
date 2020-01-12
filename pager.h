//
// Created by Colin Peppler on 1/9/20.
//

#ifndef SIMPLESQLITE_PAGER_H
#define SIMPLESQLITE_PAGER_H

#include <stdint.h>
#include <fcntl.h>
#include <errno.h>

#define TABLE_MAX_PAGES 100

static const uint32_t PAGE_SIZE = 4096;

typedef struct {
    int file_descriptor;
    uint32_t file_length;
    void *pages[TABLE_MAX_PAGES];
} Pager;

// Constructor for a Pager
Pager *pager_open(const char *filename);

// Flushes a partial or full page
void pager_flush(Pager *pager, uint32_t page_num, uint32_t size);

// Gets a page from file (for cache miss)
void *get_page(Pager *pager, uint32_t page_num);

#endif //SIMPLESQLITE_PAGER_H
