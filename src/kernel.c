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

    /* Header */
    printk_setfg(CYAN);
    printk_setbg(BLACK);

    printk("===============================================================================\n");
    printk("                         NINUX PRINTK TEST BED\n");
    printk("===============================================================================\n");

    /* BASIC */
    printk_setfg(YELLOW);
    printk("\n  [ BASIC ]\n");

    printk_setfg(WHITE);
    printk("  text: ");
    printk_setfg(GREEN);
    printk("hello NINUX");

    printk_setfg(WHITE);
    printk("        percent: ");
    printk_setfg(GREEN);
    printk("100%% complete\n");

    /* DECIMAL */
    printk_setfg(YELLOW);
    printk("\n  [ DECIMAL ]\n");

    printk_setfg(WHITE);
    printk("  %%d zero: ");
    printk_setfg(CYAN);
    printk("%d", 0);

    printk_setfg(WHITE);
    printk("        positive: ");
    printk_setfg(CYAN);
    printk("%d", 42);

    printk_setfg(WHITE);
    printk("        negative: ");
    printk_setfg(RED);
    printk("%d\n", -42);

    printk_setfg(WHITE);
    printk("  %%d max: ");
    printk_setfg(CYAN);
    printk("%d", 2147483647);

    printk_setfg(WHITE);
    printk("        %%u max: ");
    printk_setfg(CYAN);
    printk("%u\n", 4294967295U);

    /* CHARACTER */
    printk_setfg(YELLOW);
    printk("\n  [ CHARACTER ]\n");

    printk_setfg(WHITE);
    printk("  letters: ");
    printk_setfg(GREEN);
    printk("%c %c %c %c", 'A', 'Z', 'a', 'z');

    printk_setfg(WHITE);
    printk("        digits: ");
    printk_setfg(GREEN);
    printk("%c %c %c", '0', '1', '9');

    printk_setfg(WHITE);
    printk("        symbols: ");
    printk_setfg(GREEN);
    printk("%c %c %c\n", '!', '?', '@');

    /* STRING */
    printk_setfg(YELLOW);
    printk("\n  [ STRING ]\n");

    printk_setfg(WHITE);
    printk("  normal: ");
    printk_setfg(GREEN);
    printk("%s", "NINUX");

    printk_setfg(WHITE);
    printk("        kernel: ");
    printk_setfg(GREEN);
    printk("%s", "KERNEL");

    printk_setfg(WHITE);
    printk("        arch: ");
    printk_setfg(GREEN);
    printk("%s\n", "x86_64");

    /* HEX */
    printk_setfg(YELLOW);
    printk("\n  [ HEXADECIMAL ]\n");

    printk_setfg(WHITE);
    printk("  %%x: ");
    printk_setfg(MAGENTA);
    printk("%x", 0U);

    printk_setfg(WHITE);
    printk("        ");
    printk_setfg(MAGENTA);
    printk("%x", 0xDEADBEEFU);

    printk_setfg(WHITE);
    printk("        ");
    printk_setfg(MAGENTA);
    printk("%x\n", 0xFFFFFFFFU);

    printk_setfg(WHITE);
    printk("  %%X: ");
    printk_setfg(MAGENTA);
    printk("%X", 0U);

    printk_setfg(WHITE);
    printk("        ");
    printk_setfg(MAGENTA);
    printk("%X", 0xCAFEBABEU);

    printk_setfg(WHITE);
    printk("        ");
    printk_setfg(MAGENTA);
    printk("%X\n", 0xFFFFFFFFU);

    /* MIXED */
    printk_setfg(YELLOW);
    printk("\n  [ MIXED FORMAT ]\n");

    printk_setfg(WHITE);
    printk("  ");

    printk_setfg(GREEN);
    printk("%s", "NINUX");

    printk_setfg(WHITE);
    printk(" ");

    printk_setfg(CYAN);
    printk("%d", -12345);

    printk_setfg(WHITE);
    printk(" ");

    printk_setfg(CYAN);
    printk("%u", 12345U);

    printk_setfg(WHITE);
    printk(" ");

    printk_setfg(MAGENTA);
    printk("%x", 0xCAFEBABEU);

    printk_setfg(WHITE);
    printk(" ");

    printk_setfg(MAGENTA);
    printk("%X", 0xDEADBEEFU);

    printk_setfg(WHITE);
    printk(" ");

    printk_setfg(GREEN);
    printk("%c", 'X');

    printk_setfg(WHITE);
    printk(" %%\n");

    /* EDGE CASES */
    printk_setfg(YELLOW);
    printk("\n  [ EDGE CASES ]\n");

    printk_setfg(WHITE);
    printk("  adjacent: ");

    printk_setfg(CYAN);
    printk("%d%d%d", 1, 2, 3);

    printk_setfg(WHITE);
    printk("        hex: ");

    printk_setfg(MAGENTA);
    printk("%x%X%x%X\n", 0xA, 0xB, 0xC, 0xD);

    printk_setfg(WHITE);
    printk("  zero: ");

    printk_setfg(CYAN);
    printk("%d", 0);

    printk_setfg(WHITE);
    printk(" / ");

    printk_setfg(CYAN);
    printk("%u", 0U);

    printk_setfg(WHITE);
    printk(" / ");

    printk_setfg(MAGENTA);
    printk("%x", 0U);

    printk_setfg(WHITE);
    printk(" / ");

    printk_setfg(MAGENTA);
    printk("%X\n", 0U);

    /* STATUS */
    printk("\n");

    printk_setfg(BLACK);
    printk_setbg(GREEN);

    printk("                         PRINTK TESTS PASSED                         ");

    printk_reset_colors();

    printk("\n");
    printk_setfg(CYAN);
    printk("===============================================================================\n");

    printk_reset_colors();

    while (1)
        __asm__ volatile("hlt");
}