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
printk("================ PRINTK STRESS ================\n");

printk("d: %d %d %d\n", 0, 42, -42);
printk("u: %u %u\n", 0U, 4294967295U);
printk("c: %c %c %c %c\n", 'A', 'Z', '!', '?');
printk("s: %s | %s\n", "NINUX", "KERNEL");
printk("x: %x %x %x\n", 0U, 0xDEADBEEFU, 0xFFFFFFFFU);
printk("X: %X %X %X\n", 0U, 0xDEADBEEFU, 0xFFFFFFFFU);
printk("%%: 100%% complete\n");

printk("\nMixed:\n");
printk("%s %d %u %x %X %c %%\n",
       "Ninux", -12345, 12345U,
       0xCAFEBABEU, 0xDEADBEEFU, 'X');

printk("\nBuffer: ");
for (uint32_t i = 0; i < 20; i++)
    printk("%u ", i);

printk("\n==================== DONE ====================\n");

    while (1) {
        __asm__ volatile("hlt");
    }
}


