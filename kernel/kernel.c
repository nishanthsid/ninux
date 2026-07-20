#include <boot.h>
#include <types.h>
#include <video/framebuffer.h>
#include <video/console.h>
#include <video/color.h>

void kernel_main(BootInfo *Boot){
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
    "==================== ALL SYSTEMS NOMINAL ====================\n",
    BLACK, LIME);

    while(1);
}
