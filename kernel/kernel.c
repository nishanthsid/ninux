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

    _console_put_string(&buffer[i]);
}

void kernel_main(BootInfo *Boot)
{
    framebuffer_init(Boot);
    console_init();
    fb_fill(BLACK);

    _console_put_string_color(
        "==========================================================================\n",
        BLACK, CYAN);
    _console_put_string_color(
        "              NINUX STRATEGIC COMMAND TERMINAL v0.1                       \n",
        BLACK, CYAN);
    _console_put_string_color(
        "==========================================================================\n\n",
        BLACK, CYAN);

    _console_put_string("[SYSTEM] Boot Sequence....................... ");
    _console_put_string_color(" COMPLETE ", BLACK, LIME);
    _console_put_string("\n");

    _console_put_string("[CPU] AMD64 Long Mode........................ ");
    _console_put_string_color(" ONLINE ", BLACK, GREEN);
    _console_put_string("\n");

    _console_put_string("[MEMORY] Physical Memory Manager............. ");
    _console_put_string_color(" READY ", BLACK, GREEN);
    _console_put_string("\n");

    _console_put_string("[VIDEO] GOP Framebuffer...................... ");
    _console_put_string_color(" ACTIVE ", BLACK, CYAN);
    _console_put_string("\n");

    _console_put_string("[VIDEO] Console Driver....................... ");
    _console_put_string_color(" LOADED ", BLACK, CYAN);
    _console_put_string("\n");

    _console_put_string("[SECURITY] Kernel Lockdown................... ");
    _console_put_string_color(" ENABLED ", BLACK, GREEN);
    _console_put_string("\n\n");

    _console_put_string_color(
        "====================== MISSILE CONTROL ======================\n",
        BLACK, YELLOW);

    _console_put_string("SILO-01  STATUS ");
    _console_put_string_color(" ARMED ", WHITE, RED);
    _console_put_string("   TARGET LOCK ");
    _console_put_string_color(" YES ", BLACK, GREEN);
    _console_put_string("\n");

    _console_put_string("SILO-02  STATUS ");
    _console_put_string_color(" STANDBY ", BLACK, YELLOW);
    _console_put_string(" TARGET LOCK ");
    _console_put_string_color(" NO ", WHITE, RED);
    _console_put_string("\n");

    _console_put_string("SILO-03  STATUS ");
    _console_put_string_color(" OFFLINE ", BLACK, GRAY);
    _console_put_string(" TARGET LOCK ");
    _console_put_string_color(" --- ", BLACK, GRAY);
    _console_put_string("\n");

    _console_put_string("SILO-04  STATUS ");
    _console_put_string_color(" READY ", BLACK, LIME);
    _console_put_string("   TARGET LOCK ");
    _console_put_string_color(" YES ", BLACK, GREEN);
    _console_put_string("\n\n");

    _console_put_string_color(
        "======================== LIVE EVENTS ========================\n",
        BLACK, BLUE);

    _console_put_string("[00:00:01] UEFI GOP initialized\n");
    _console_put_string("[00:00:02] ELF kernel loaded\n");
    _console_put_string("[00:00:03] Framebuffer mapped\n");
    _console_put_string("[00:00:04] Console initialized\n");
    _console_put_string("[00:00:05] Video diagnostics complete\n");
    _console_put_string("[00:00:06] Awaiting launch authorization...\n\n");

    _console_put_string("AUTHORIZATION ");
    _console_put_string_color(" DENIED ", WHITE, RED);
    _console_put_string("\n");

    _console_put_string("REASON        ");
    _console_put_string_color(" DEVELOPMENT BUILD ", BLACK, MAGENTA);
    _console_put_string("\n\n");

    _console_put_string_color(
        "==================== ALL SYSTEMS NOMINAL ====================\n\n",
        BLACK, LIME);

    uint32_t counter = 1;

    while (1) {

        // console_put_string("[LOG ");

        // if (counter < 10)
        //     console_put_string("000");
        // else if (counter < 100)
        //     console_put_string("00");
        // else if (counter < 1000)
        //     console_put_string("0");

        // console_put_uint(counter);

        // console_put_string("] ");

        // switch (counter % 8) {
        //     case 0:
        //         console_put_string_color("INFO ", BLACK, CYAN);
        //         break;
        //     case 1:
        //         console_put_string_color("OK ", BLACK, GREEN);
        //         break;
        //     case 2:
        //         console_put_string_color("WARN ", BLACK, YELLOW);
        //         break;
        //     case 3:
        //         console_put_string_color("ERROR ", WHITE, RED);
        //         break;
        //     case 4:
        //         console_put_string_color("DEBUG ", BLACK, MAGENTA);
        //         break;
        //     case 5:
        //         console_put_string_color("TRACE ", BLACK, BLUE);
        //         break;
        //     case 6:
        //         console_put_string_color("READY ", BLACK, LIME);
        //         break;
        //     default:
        //         console_put_string_color("SYNC ", BLACK, CYAN);
        //         break;
        // }

        // console_put_string(
        //     "Kernel scrolling stress test... "
        //     "The quick brown fox jumps over the lazy dog. "
        //     "0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");

        // counter++;

        // /* Primitive busy-wait delay */
        // for (volatile uint64_t delay = 0;
        //      delay < 50000ULL;
        //      delay++)
        // {
        //     __asm__ volatile("pause");
        // }
    }
}