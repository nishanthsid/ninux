#include <console/kernc.h>

console cns;
text_buffer tb;
cell console_cells[TB_MAX_ROWS * TB_MAX_COLS];

void kernc_init(){
    uint32_t screen_rows = console_get_line_height();
    uint32_t screen_cols = console_get_line_width();
    tb_init(
        &tb,
        console_cells,
        TB_MAX_ROWS,
        TB_MAX_COLS,
        GREEN,
        BLACK
    );
    console_init(
        &cns,
        &tb,
        GREEN,
        BLACK
    );
    console_clear(&cns);
}


console *get_kernel_console(){
    return &cns;
}
