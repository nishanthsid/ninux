#include <boot.h>
#include <types.h>
#include <video/framebuffer.h>
#include <console/console.h>
#include <console/textbuffer.h>


void kernel_main(boot_info *bt_info)
{
    framebuffer_init(bt_info);
    console_sys_init();
    // uint32_t screen_rows = console_get_line_height();
    // uint32_t screen_cols = console_get_line_width();
    // tb_init(
    //     &tb,
    //     console_cells,
    //     TB_MAX_ROWS,
    //     TB_MAX_COLS,
    //     WHITE,
    //     BLACK
    // );
    // console_init(
    //     &cns,
    //     &tb,
    //     WHITE,
    //     BLACK
    // );
    // console_clear(&cns);
    // console_put_string_color(
    //     &cns,
    //     "Hello all, this is Hi from Ninux\n",
    //     BLACK,
    //     LIME
    // );
    while (1) {
        __asm__ volatile("hlt");
    }
}