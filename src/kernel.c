#include <boot.h>
#include <types.h>
#include <video/framebuffer.h>
#include <console/console.h>
#include <console/textbuffer.h>
#include <console/kernc.h>
#include <lib/printk.h>

void kernel_main(boot_info *bt_info)
{
    framebuffer_init(bt_info);
    fb_console_init();
    kernc_init();
    init_printk();

    printk("\033[36m");
    printk("==============================================================================\n");
    printk("                         NINUX PRINTK TEST BED\n");
    printk("==============================================================================\n");
    printk("\033[0m");

    /* BASIC */
    printk("\033[33m BASIC\033[0m");
    printk("                 text: \033[32mhello NINUX\033[0m");
    printk("   percent: \033[32m100%%\033[0m\n");

    /* DECIMAL */
    printk("\033[33m DECIMAL\033[0m");
    printk("               %%d: \033[36m%d  %d  %d\033[0m", 0, 42, -42);
    printk("   %%u: \033[36m%u\033[0m\n", 4294967295U);

    /* CHARACTER */
    printk("\033[33m CHARACTER\033[0m");
    printk("             chars: \033[32m%c %c %c %c %c %c %c\033[0m\n",
           'A', 'Z', 'a', 'z', '0', '!', '@');

    /* STRING */
    printk("\033[33m STRING\033[0m");
    printk("                \033[32m%s  %s  %s\033[0m\n",
           "NINUX", "KERNEL", "x86_64");

    /* HEX */
    printk("\033[33m HEX\033[0m");
    printk("                   %%x: \033[35m%x %x %x\033[0m",
           0U, 0xDEADBEEFU, 0xFFFFFFFFU);
    printk("   %%X: \033[35m%X %X\033[0m\n",
           0xCAFEBABEU, 0xFFFFFFFFU);

    /* MIXED */
    printk("\033[33m MIXED\033[0m");
    printk("                 \033[32m%s\033[0m ", "NINUX");
    printk("\033[36m%d %u\033[0m ", -12345, 12345U);
    printk("\033[35m%x %X\033[0m ", 0xCAFEBABEU, 0xDEADBEEFU);
    printk("\033[32m%c\033[0m\n", 'X');

    /* ====================================================================== */
    /* ANSI FOREGROUND                                                        */
    /* ====================================================================== */

    printk("\033[33m ANSI FG\033[0m");
    printk("                ");

    printk("\033[30mBLACK ");
    printk("\033[31mRED ");
    printk("\033[32mGREEN ");
    printk("\033[33mYELLOW ");
    printk("\033[34mBLUE ");
    printk("\033[35mMAGENTA ");
    printk("\033[36mCYAN ");
    printk("\033[37mWHITE");
    printk("\033[0m\n");

    /* ANSI BACKGROUND */

    printk("\033[33m ANSI BG\033[0m");
    printk("                ");

    printk("\033[40m BLACK ");
    printk("\033[41m RED ");
    printk("\033[42m GREEN ");
    printk("\033[43m YELLOW ");
    printk("\033[44m BLUE ");
    printk("\033[45m MAGENTA ");
    printk("\033[46m CYAN ");
    printk("\033[47m WHITE ");
    printk("\033[0m\n");

    /* ANSI FG + BG */

    printk("\033[33m ANSI FG+BG\033[0m");
    printk("             ");

    printk("\033[31m\033[40m RED/BLACK ");
    printk("\033[32m\033[41m GREEN/RED ");
    printk("\033[33m\033[44m YELLOW/BLUE ");
    printk("\033[35m\033[47m MAGENTA/WHITE");
    printk("\033[0m\n");

    /* ANSI RESET */

    printk("\033[33m ANSI RESET\033[0m");
    printk("              ");

    printk("\033[31mRED ");
    printk("\033[32mGREEN ");
    printk("\033[34mBLUE ");
    printk("\033[0mRESET ");
    printk("normal\n");

    /* ANSI DEFAULT FG/BG */

    printk("\033[33m ANSI 39/49\033[0m");
    printk("              ");

    printk("\033[31mRED ");
    printk("\033[39mDEFAULT_FG ");

    printk("\033[44mBLUE_BG ");
    printk("\033[49mDEFAULT_BG\n");

    /* ANSI RAPID TRANSITIONS */

    printk("\033[33m ANSI TRANSITIONS\033[0m       ");

    printk("\033[31mR");
    printk("\033[32mG");
    printk("\033[34mB");
    printk("\033[33mY");
    printk("\033[35mM");
    printk("\033[36mC");
    printk("\033[37mW");
    printk("\033[0m  ");

    printk("\033[41mR");
    printk("\033[42mG");
    printk("\033[44mB");
    printk("\033[43mY");
    printk("\033[45mM");
    printk("\033[46mC");
    printk("\033[47mW");
    printk("\033[0m\n");

    /* ANSI INLINE */

    printk("\033[33m ANSI INLINE\033[0m");
    printk("              ");

    printk("normal ");
    printk("\033[31mRED ");
    printk("\033[32mGREEN ");
    printk("\033[34mBLUE ");
    printk("\033[0mnormal ");
    printk("\033[33mYELLOW ");
    printk("\033[0mnormal\n");

    /* ANSI + FORMAT */

    printk("\033[33m ANSI + FORMAT\033[0m");
    printk("             ");

    printk("\033[36mvalue=%d ", 42);
    printk("\033[35mhex=%x ", 0xDEADBEEFU);
    printk("\033[32mstr=%s ", "NINUX");
    printk("\033[31mchar=%c", 'X');
    printk("\033[0m\n");

    /* EDGE CASES */

    printk("\033[33m EDGE CASES\033[0m");
    printk("               ");

    printk("adjacent: \033[36m%d%d%d\033[0m", 1, 2, 3);
    printk("  hex: \033[35m%x%X%x%X\033[0m", 0xA, 0xB, 0xC, 0xD);
    printk("  zero: \033[36m%d/%u\033[0m", 0, 0U);
    printk("/\033[35m%x/%X\033[0m\n", 0U, 0U);

    /* PASS */

    printk("\n");

    printk("\033[30m\033[42m");
    printk("                         PRINTK TESTS PASSED                         ");
    printk("\033[0m\n");

    printk("\033[36m");
    printk("==============================================================================\n");
    printk("\033[0m");

    while (1)
        __asm__ volatile("hlt");
}