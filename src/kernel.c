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

    printk("\n");
    printk("============================================================\n");
    printk("                 Ninux Kernel Version - %d                  \n", -234);
    printk("============================================================\n");
    printk("\n");

    printk("Testing printk machinery...\n");

    printk("signed:   %d\n", -123456);
    printk("unsigned: %u\n", 123456U);
    printk("char:     %c\n", 'X');
    printk("string:   %s\n", "NINUX");
    printk("percent:  100%%\n");

    printk("\n");
    printk("Mixed: %s %d %u %c %%\n",
        "Ninux",
        -42,
        42U,
        '!');

    while (1) {
        __asm__ volatile("hlt");
    }
}


