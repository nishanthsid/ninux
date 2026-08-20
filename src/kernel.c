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
    printk("                 N I N U X   K E R N E L                  \n");
    printk("============================================================\n");
    printk("\n");

    printk("[BOOT] Power-on sequence initiated\n");
    printk("[BOOT] Entering kernel execution environment\n");
    printk("[BOOT] UEFI handoff accepted\n");
    printk("\n");

    printk("[INIT] Initializing framebuffer ................. OK\n");
    printk("[INIT] Initializing text console ................ OK\n");
    printk("[INIT] Initializing kernel console .............. OK\n");
    printk("[INIT] Initializing printk subsystem ............ OK\n");
    printk("\n");

    printk("[ OK ] Kernel console online\n");
    printk("[ OK ] Terminal output online\n");
    printk("[ OK ] Kernel logging online\n");
    printk("\n");

    printk("------------------------------------------------------------\n");
    printk("                 NINUX STRATEGIC COMMAND                    \n");
    printk("                    TERMINAL v0.1                           \n");
    printk("------------------------------------------------------------\n");
    printk("\n");

    printk("STATUS: SYSTEM ONLINE\n");
    printk("STATUS: ALL CORE SYSTEMS NOMINAL\n");
    printk("\n");

    printk("ninux> ");
    
    while (1) {
        __asm__ volatile("hlt");
    }
}


