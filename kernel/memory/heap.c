#include "../include/heap.h"
#include <stdint.h>

#define HEAP_SIZE 10 * 1024 * 1024
#define BLOCK_HEADER_SIZE sizeof(HeapBlock)

typedef struct HeapBlock {
    size_t size;            
    int is_free;             
    struct HeapBlock* next;  
} HeapBlock;

uint8_t heap[HEAP_SIZE];
HeapBlock* free_list;

void init_heap() {
    free_list = (HeapBlock*)heap; 
    free_list->size = HEAP_SIZE - BLOCK_HEADER_SIZE;  
    free_list->is_free = 1;
    free_list->next = NULL;
}

// Split a block into two if there is excess space
void split_block(HeapBlock* block, size_t size) {
    size_t remaining_size = block->size - size - BLOCK_HEADER_SIZE;
    if (remaining_size >= BLOCK_HEADER_SIZE + 8) {  // Check if there's enough space for a new block
        HeapBlock* new_block = (HeapBlock*)((uint8_t*)block + BLOCK_HEADER_SIZE + size);
        new_block->size = remaining_size;
        new_block->is_free = 1;
        new_block->next = block->next;
        block->size = size;
        block->next = new_block;
    }
}

// Allocate memory
void* malloc(size_t size) {
    size = (size + 7) & ~7;
    HeapBlock* current = free_list;
    while (current) {
        if (current->is_free && current->size >= size) {
            // If the block is large enough, split it
            if (current->size > size + BLOCK_HEADER_SIZE) {
                split_block(current, size);
            }
            current->is_free = 0;  // Mark the block as allocated
            return (void*)((uint8_t*)current + BLOCK_HEADER_SIZE);
        }
        current = current->next;
    }
    return NULL;  // No suitable block found
}

void free(void* ptr) {

}