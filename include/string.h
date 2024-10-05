//
// Created by linus on 21.09.24.
//

#ifndef STRING_H
#define STRING_H
#include <stdint.h>
#include "stddef.h"

const char* to_string(uint64_t value);
const char* to_string(int64_t value);
const char* to_hstring(uint64_t value);
const char* to_hstring(uint32_t value);
const char* to_hstring(uint16_t value);
const char* to_hstring(uint8_t value);
const char* to_string(double value, uint8_t decimalPlaces);
const char* to_string(double value);

size_t strlen(const char *str);

#endif //STRING_H