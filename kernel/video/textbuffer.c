#include <video/textbuffer.h>
#include <video/color.h>
#include <lib/memshift.h>

Cell get_cell(char c, Color fg, Color bg){
    return (Cell){
        .c = c,
        .fg = fg,
        .bg = bg
    };
}

void text_buffer_init(
    TextBuffer *tb, 
    Cell *cells, 
    uint32_t visible_rows, 
    uint32_t cols,
    uint32_t history_rows,
    Color default_fg,
    Color default_bg){
        tb->cells = cells;
        tb->cols = cols;
        tb->current_cell = 0;
        tb->history_rows = history_rows;
        tb->visible_rows = visible_rows;
        tb->scroll_offset = 0;
        tb->default_bg = default_bg;
        tb->default_fg = default_fg;
}

void tb_putchar(TextBuffer *tb, char c){
    tb_putchar_color(tb, c, tb->default_fg, tb->default_bg);
}

void tb_putchar_color(TextBuffer *tb, char c, Color fg, Color bg){
    Cell cell = get_cell(c, fg, bg);
    tb->cells[tb->current_cell++] = cell;
    if(tb->current_cell >= tb->history_rows * tb->cols){
        mem_shift(tb->cells, tb->history_rows*tb->cols*sizeof(Cell), SHIFT_LEFT, sizeof(Cell));
        tb->current_cell = tb->history_rows * tb->cols - 1;
    }
}


void tb_puts_color(TextBuffer *tb, const char *string, Color fg, Color bg){
    uint32_t index = 0;
    while(string[index] != 0){
        tb_putchar_color(tb, string[index], fg, bg);
        index++;
    }
}

void tb_puts(TextBuffer *tb, const char *string){
    tb_puts_color(tb, string, tb->default_fg, tb->default_bg);
}


