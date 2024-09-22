//
// Created by linus on 20.09.24.
//
#include "../include/bitmap.h"

bool Bitmap_Get(Bitmap* bitmap, uint64_t index) {
    uint64_t byteIndex = index / 8;            // Find which byte the bit is in
    uint8_t bitIndex = index % 8;              // Find which bit within the byte
    uint8_t bitIndexer = 0b10000000 >> bitIndex; // Create a mask to isolate the bit
    if ((bitmap->Buffer[byteIndex] & bitIndexer) > 0) {
        return true; // Bit is set to 1
    }
    return false; // Bit is set to 0
}

void Bitmap_Set(Bitmap* bitmap, uint64_t index, bool value) {
    uint64_t byteIndex = index / 8;            // Find which byte the bit is in
    uint8_t bitIndex = index % 8;              // Find which bit within the byte
    uint8_t bitIndexer = 0b10000000 >> bitIndex; // Create a mask to isolate the bit

    // Clear the bit first
    bitmap->Buffer[byteIndex] &= ~bitIndexer;

    // If value is true, set the bit
    if (value) {
        bitmap->Buffer[byteIndex] |= bitIndexer;
    }
}