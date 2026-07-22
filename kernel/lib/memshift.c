#include <lib/memshift.h>

void mem_shift(void * memory, uint32_t memory_size, uint8_t shift_direction, uint32_t shift_positions){
    if (shift_positions == 0){
        return;
    }
    uint8_t *mem = (uint8_t *)memory;
    if (shift_positions >= memory_size) {
        for (uint32_t i = 0; i < memory_size; i++)
            mem[i] = 0;
        return;
    }
    if(shift_direction == SHIFT_LEFT){
        for(uint32_t i = shift_positions;i < memory_size;i++){
            mem[i - shift_positions] = mem[i];
        }
        for(uint32_t i = memory_size - shift_positions;i < memory_size; i++){
            mem[i] = 0;
        }
    }
    else if(shift_direction == SHIFT_RIGHT){
        for(int32_t i = (int32_t)(memory_size - shift_positions - 1);i >= 0;i--){
            mem[i + shift_positions] = mem[i];
        }
        for(uint32_t i = 0; i < shift_positions; i++){
            mem[i] = 0;
        }
    }
}