#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H

#include <types.h>
#include <video/color.h>

typedef struct {
    Color fg;
    Color bg;
    char c;
} Cell;

typedef struct {
    Cell *cells;
    uint32_t visible_rows;
    uint32_t cols;
    uint32_t history_rows;
    uint32_t scroll_offset;
} TextBuffer;

#endif