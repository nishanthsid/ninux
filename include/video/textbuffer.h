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
    uint32_t current_cell;
    Color default_fg;
    Color default_bg;
} TextBuffer;

void text_buffer_init(
    TextBuffer *tb,
    Cell *cells,
    uint32_t visible_rows,
    uint32_t cols, 
    uint32_t history_rows,
    Color default_fg,
    Color default_bg
);


void tb_putchar(TextBuffer *tb, char c);
void tb_putchar_color(TextBuffer *tb, char c, Color fg, Color bg);

void tb_puts(TextBuffer *tb, const char *string);
void tb_puts_color(TextBuffer *tb, const char *string, Color fg, Color bg);



#endif