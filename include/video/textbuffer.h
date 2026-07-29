#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H

#include <types.h>
#include <video/color.h>

#define SCROLL_UP 1
#define SCROLL_DOWN 0

//Errors

#define TB_ERROR 1 << 32 - 1

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
    uint32_t capacity;
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

void tb_set_cursor(TextBuffer *tb, uint32_t cursor_x, uint32_t cursor_y);
uint32_t tb_get_cursor_x(TextBuffer *tb);
uint32_t tb_get_cursor_y(TextBuffer *tb);

void tb_scroll(TextBuffer *tb, uint8_t scroll_direction, uint32_t scroll_rows);
void tb_scroll_to(TextBuffer *tb, uint32_t row);


#endif