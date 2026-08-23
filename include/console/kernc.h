#ifndef KERNC_H
#define KERNC_H

#include <console/console.h>
#include <console/textbuffer.h>

#define TB_MAX_ROWS 512
#define TB_MAX_COLS 160

extern console cns;
extern text_buffer tb;
extern cell console_cells[TB_MAX_ROWS * TB_MAX_COLS];

void kernc_init();

console *get_kernel_console();

#endif