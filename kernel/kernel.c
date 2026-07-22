#include <boot.h>
#include <types.h>
#include <video/framebuffer.h>
#include <video/console.h>
#include <video/color.h>

static void console_put_uint(uint32_t value) {
    char buffer[11];
    int i = 10;

    buffer[i] = '\0';

    do {
        buffer[--i] = '0' + (value % 10);
        value /= 10;
    } while (value);

    console_put_string(&buffer[i]);
}

void kernel_main(BootInfo *Boot)
{
    framebuffer_init(Boot);
    console_init();
    fb_fill(BLACK);

    console_set_fg(WHITE);
    console_set_bg(BLACK);

    console_put_string_color(
        "==========================================================================\n",
        BLACK, CYAN);
    console_put_string_color(
        "              NINUX STRATEGIC COMMAND TERMINAL v0.1                       \n",
        BLACK, CYAN);
    console_put_string_color(
        "==========================================================================\n\n",
        BLACK, CYAN);

    console_put_string("[SYSTEM] Boot Sequence....................... ");
    console_put_string_color(" COMPLETE ", BLACK, LIME);
    console_put_string("\n");

    console_put_string("[CPU] AMD64 Long Mode........................ ");
    console_put_string_color(" ONLINE ", BLACK, GREEN);
    console_put_string("\n");

    console_put_string("[MEMORY] Physical Memory Manager............. ");
    console_put_string_color(" READY ", BLACK, GREEN);
    console_put_string("\n");

    console_put_string("[VIDEO] GOP Framebuffer...................... ");
    console_put_string_color(" ACTIVE ", BLACK, CYAN);
    console_put_string("\n");

    console_put_string("[VIDEO] Console Driver....................... ");
    console_put_string_color(" LOADED ", BLACK, CYAN);
    console_put_string("\n");

    console_put_string("[SECURITY] Kernel Lockdown................... ");
    console_put_string_color(" ENABLED ", BLACK, GREEN);
    console_put_string("\n\n");

    console_put_string_color(
        "====================== MISSILE CONTROL ======================\n",
        BLACK, YELLOW);

    console_put_string("SILO-01  STATUS ");
    console_put_string_color(" ARMED ", WHITE, RED);
    console_put_string("   TARGET LOCK ");
    console_put_string_color(" YES ", BLACK, GREEN);
    console_put_string("\n");

    console_put_string("SILO-02  STATUS ");
    console_put_string_color(" STANDBY ", BLACK, YELLOW);
    console_put_string(" TARGET LOCK ");
    console_put_string_color(" NO ", WHITE, RED);
    console_put_string("\n");

    console_put_string("SILO-03  STATUS ");
    console_put_string_color(" OFFLINE ", BLACK, GRAY);
    console_put_string(" TARGET LOCK ");
    console_put_string_color(" --- ", BLACK, GRAY);
    console_put_string("\n");

    console_put_string("SILO-04  STATUS ");
    console_put_string_color(" READY ", BLACK, LIME);
    console_put_string("   TARGET LOCK ");
    console_put_string_color(" YES ", BLACK, GREEN);
    console_put_string("\n\n");

    console_put_string_color(
        "======================== LIVE EVENTS ========================\n",
        BLACK, BLUE);

    console_put_string("[00:00:01] UEFI GOP initialized\n");
    console_put_string("[00:00:02] ELF kernel loaded\n");
    console_put_string("[00:00:03] Framebuffer mapped\n");
    console_put_string("[00:00:04] Console initialized\n");
    console_put_string("[00:00:05] Video diagnostics complete\n");
    console_put_string("[00:00:06] Awaiting launch authorization...\n\n");

    console_put_string("AUTHORIZATION ");
    console_put_string_color(" DENIED ", WHITE, RED);
    console_put_string("\n");

    console_put_string("REASON        ");
    console_put_string_color(" DEVELOPMENT BUILD ", BLACK, MAGENTA);
    console_put_string("\n\n");

    console_put_string_color(
        "==================== ALL SYSTEMS NOMINAL ====================\n\n",
        BLACK, LIME);

    uint32_t counter = 1;

    while (1) {

        console_put_string("[LOG ");

        if (counter < 10)
            console_put_string("000");
        else if (counter < 100)
            console_put_string("00");
        else if (counter < 1000)
            console_put_string("0");

        console_put_uint(counter);

        console_put_string("] ");

        switch (counter % 8) {
            case 0:
                console_put_string_color("INFO ", BLACK, CYAN);
                break;
            case 1:
                console_put_string_color("OK ", BLACK, GREEN);
                break;
            case 2:
                console_put_string_color("WARN ", BLACK, YELLOW);
                break;
            case 3:
                console_put_string_color("ERROR ", WHITE, RED);
                break;
            case 4:
                console_put_string_color("DEBUG ", BLACK, MAGENTA);
                break;
            case 5:
                console_put_string_color("TRACE ", BLACK, BLUE);
                break;
            case 6:
                console_put_string_color("READY ", BLACK, LIME);
                break;
            default:
                console_put_string_color("SYNC ", BLACK, CYAN);
                break;
        }

        console_put_string(
            "Kernel scrolling stress test... "
            "The quick brown fox jumps over the lazy dog. "
            "0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");

        counter++;

        /* Primitive busy-wait delay */
        for (volatile uint64_t delay = 0;
             delay < 5000000ULL;
             delay++)
        {
            __asm__ volatile("pause");
        }
    }
}