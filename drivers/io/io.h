//
// Created by linus on 05.10.24.
//

#ifndef IO_H
#define IO_H
#include <stdint.h>

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
void io_wait();

#endif //IO_H