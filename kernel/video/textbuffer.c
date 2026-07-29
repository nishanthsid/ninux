#include <video/textbuffer.h>
#include <video/color.h>
#include <lib/memshift.h>

static inline Cell get_cell(char c, Color fg, Color bg){
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
        tb->capacity = history_rows * cols;
        for (uint32_t i = 0; i < tb->capacity; i++) {
            tb->cells[i] = get_cell(' ', default_fg, default_bg);
        }
}

void tb_putchar(TextBuffer *tb, char c){
    tb_putchar_color(tb, c, tb->default_fg, tb->default_bg);
}

void tb_putchar_color(TextBuffer *tb, char c, Color fg, Color bg){
    uint32_t cells_needed = 1;
    uint8_t is_regular_char = 1;
    if(c == '\n'){
        is_regular_char = 0;
        uint32_t next_line = (tb->current_cell / tb->cols + 1) * tb->cols;
        cells_needed = next_line - tb->current_cell;
    }
    else if(c == '\t'){
        is_regular_char = 0;
        cells_needed = 4;
    }

    if(tb->current_cell + cells_needed > tb->capacity){
        mem_shift(tb->cells, tb->capacity*sizeof(Cell), SHIFT_LEFT, (tb->current_cell + cells_needed - tb->capacity)*sizeof(Cell));
        tb->current_cell = tb->capacity - cells_needed;
    }

    for(uint32_t i = 0;i < cells_needed - 1;i++){
        Cell cell = get_cell(' ', fg, bg);
        tb->cells[tb->current_cell++] = cell;
    }
    Cell cell;

    if(is_regular_char) cell = get_cell(c, fg, bg);
    else cell = get_cell(' ', fg, bg);
    
    tb->cells[tb->current_cell++] = cell;
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

void tb_set_cursor(TextBuffer *tb, uint32_t cursor_x, uint32_t cursor_y){
    tb->current_cell = cursor_x * tb->cols + cursor_y;
    if(tb->current_cell >= tb->capacity){
        tb->current_cell = tb->capacity - 1;
    }
}

uint32_t tb_get_cursor_x(TextBuffer *tb){
    if(tb->cols != 0){
        return tb->current_cell / tb->cols;
    }
    return TB_ERROR;
}

uint32_t tb_get_cursor_y(TextBuffer *tb){
    if(tb->cols != 0){
        return tb->current_cell % tb->cols;
    }
    return TB_ERROR;
}

void tb_scroll(TextBuffer *tb, uint8_t scroll_direction, uint32_t scroll_rows){
    uint32_t cur_x = tb_get_cursor_x(tb);
    uint32_t cur_y = tb_get_cursor_y(tb);
    if(scroll_direction == SCROLL_UP){
        if(scroll_rows > cur_x) scroll_rows = cur_x;
        tb->scroll_offset = cur_x - scroll_rows;
    }
    else if(scroll_direction == SCROLL_DOWN){
        if(scroll_rows > (tb->history_rows - cur_x)) scroll_rows = tb->history_rows - cur_x;
        tb->scroll_offset = cur_x + scroll_rows;
    }
}
void tb_scroll_to(TextBuffer *tb, uint32_t row){
    if(row > tb->history_rows) return;
    tb->scroll_offset = row;
}
