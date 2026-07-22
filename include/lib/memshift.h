#ifndef MEMMOVE_H
#define MEMMOVE_H

#define SHIFT_RIGHT 0
#define SHIFT_LEFT 1

#include <types.h>

void mem_shift(void * mem, uint32_t memory_size ,uint8_t shift_direction, uint32_t shift_positions);

#endif