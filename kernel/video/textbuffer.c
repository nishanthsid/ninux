#include <video/textbuffer.h>
#include <video/color.h>

static inline cell get_cell(char c, color24 fg, color24 bg){
    return (cell){
        .c = c,
        .fg = fg,
        .bg = bg
    };
}

static inline uint32_t get_index(text_buffer *tb, uint32_t row, uint32_t col){
    return tb->cols * row + col;
}

static inline tb_status check_index(text_buffer *tb, uint32_t row, uint32_t col, uint32_t *index){
    if (row >= tb->rows || col >= tb->cols)
    return TBERROR_OUT_OF_BOUNDS;

    *index = row * tb->cols + col;  
    return TB_OK;
}

void tb_init(text_buffer *tb, cell *cells, uint32_t rows, uint32_t cols,color24 default_fg, color24 default_bg){
        tb->cells = cells;
        tb->cols = cols;
        tb->rows = rows;
        tb->default_bg = default_bg;
        tb->default_fg = default_fg;
        tb->capacity = rows * cols;
        for (uint32_t i = 0; i < tb->capacity; i++) {
            tb->cells[i] = get_cell(' ', default_fg, default_bg);
        }
}


tb_status tb_putchar(text_buffer *tb, uint32_t row, uint32_t col, char c){
    return tb_putchar_color(tb, row, col, c, tb->default_fg, tb->default_bg);
}

tb_status tb_putchar_color(text_buffer *tb,  uint32_t row, uint32_t col, char c, color24 fg, color24 bg){
    uint32_t index = 0;
    tb_status vaild = check_index(tb, row, col, &index);
    if(vaild == TB_OK){
        tb->cells[index] = get_cell(c, fg, bg);
    }
    return vaild;
}

cell *tb_getcell(text_buffer *tb, uint32_t row, uint32_t col){
    uint32_t index = 0;
    tb_status vaild = check_index(tb, row, col, &index);
    if(vaild == TB_OK){
        return &tb->cells[index];
    }
    return NULL;
}


tb_status tb_setcell(text_buffer *tb, uint32_t row, uint32_t col, cell cl){
    uint32_t index = 0;
    tb_status vaild = check_index(tb, row, col, &index);
    if(vaild == TB_OK){
        tb->cells[index] = cl;
    }
    return vaild;
}

tb_status tb_fill_color(text_buffer *tb, char c, color24 fg, color24 bg){
    for(uint32_t index = 0; index < tb->capacity; index++){
        tb->cells[index] = get_cell(c, fg, bg);
    }
    return TB_OK;
}

tb_status tb_fill(text_buffer *tb, char c){
    return tb_fill_color(tb, c, tb->default_fg, tb->default_bg);
}

tb_status tb_clear(text_buffer *tb){
    return tb_fill_color(tb, ' ', tb->default_fg, tb->default_bg);
}

tb_status tb_copy_cell(text_buffer *tb, uint32_t source_row, uint32_t source_col, uint32_t target_row, uint32_t target_col){
    uint32_t source_index = 0, target_index = 0;
    tb_status source_valid = check_index(tb, source_row, source_col, &source_index);
    tb_status target_valid = check_index(tb, target_row, target_col, &target_index);

    if(source_valid == TB_OK && target_valid == TB_OK){
        cell tc = tb->cells[target_index];
        cell sc = tb->cells[source_index];
        tb->cells[target_index] = get_cell(sc.c, sc.fg, sc.bg);
        return TB_OK;
    }

    return TBERROR_OUT_OF_BOUNDS;
}