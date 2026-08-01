#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H

#include <types.h>
#include <video/color.h>

#define SCROLL_UP 1
#define SCROLL_DOWN 0

// text_buffer Status Enum
typedef enum {
    TB_OK,
    TBERROR_OUT_OF_BOUNDS
} tb_status;


typedef struct {
    color24 fg;
    color24 bg;
    char c;
} cell;

typedef struct {
    cell *cells;
    uint32_t rows;
    uint32_t cols;
    uint32_t capacity;
    color24 default_fg;
    color24 default_bg;
} text_buffer;

void tb_init(
    text_buffer *tb,
    cell *cells,
    uint32_t rows,
    uint32_t cols, 
    color24 default_fg,
    color24 default_bg
);


//Some properties of this text buffer should go to console

tb_status tb_putchar(text_buffer *tb, uint32_t row, uint32_t col, char c);
tb_status tb_putchar_color(text_buffer *tb,  uint32_t row, uint32_t col, char c, color24 fg, color24 bg);

cell *tb_getcell(text_buffer *tb, uint32_t row, uint32_t col);
tb_status tb_setcell(text_buffer *tb, uint32_t row, uint32_t col, cell cl);
tb_status tb_fill_color(text_buffer *tb, char c, color24 fg, color24 bg);
tb_status tb_fill(text_buffer *tb, char c);
tb_status tb_clear(text_buffer *tb);

tb_status tb_copy_cell(text_buffer *tb, uint32_t source_row, uint32_t source_col, uint32_t target_row, uint32_t target_col);

#endif