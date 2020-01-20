//
// Created by Colin Peppler on 1/9/20.
//

#ifndef SIMPLESQLITE_PAGER_H
#define SIMPLESQLITE_PAGER_H

#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <zconf.h>
#include <stdlib.h>
#include <stdio.h>

#define TABLE_MAX_PAGES 100

static const uint32_t PAGE_SIZE = 4096;

typedef struct {
    int file_descriptor;
    uint32_t file_length;
    uint32_t num_pages;
    void *pages[TABLE_MAX_PAGES];
} Pager;

// Constructor for a Pager
Pager *pager_open(const char *filename);

// Flushes a partial or full page
void pager_flush(Pager *pager, uint32_t page_num);

// Gets a page from file (for cache miss)
void *get_page(Pager *pager, uint32_t page_num);

// Finds an open page
uint32_t get_unused_page_num(Pager* pager);

#endif //SIMPLESQLITE_PAGER_H
