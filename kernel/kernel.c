#include <boot.h>
#include <types.h>
#include <video/framebuffer.h>
#include <video/console.h>
#include <video/textbuffer.h>
#include <video/color.h>

#define TB_MAX_ROWS 100
#define TB_MAX_COLS 160

static cell console_cells[TB_MAX_ROWS * TB_MAX_COLS];
static text_buffer tb;
static console cns;

static void console_put_uint(uint32_t value)
{
    char buffer[11];
    int i = 10;

    buffer[i] = '\0';

    do {
        buffer[--i] = '0' + (value % 10);
        value /= 10;
    } while (value);

    console_put_string(&cns, &buffer[i]);
}

void kernel_main(BootInfo *Boot)
{
    framebuffer_init(Boot);

    console_sys_init();

    fb_fill(BLACK);

    uint32_t rows = console_get_line_height();
    uint32_t cols = console_get_line_width();

    /*
     * TextBuffer owns the dimensions of its storage.
     *
     * For now the buffer is screen-sized.
     */
    tb_init(
        &tb,
        console_cells,
        rows,
        cols,
        WHITE,
        BLACK
    );

    console_init(
        &cns,
        &tb,
        WHITE,
        BLACK
    );

    console_put_string_color(
        &cns,
        "==========================================================================\n",
        BLACK,
        CYAN
    );

    console_put_string_color(
        &cns,
        "              NINUX STRATEGIC COMMAND TERMINAL v0.1                       \n",
        BLACK,
        CYAN
    );

    console_put_string_color(
        &cns,
        "==========================================================================\n\n",
        BLACK,
        CYAN
    );

    console_put_string(
        &cns,
        "[SYSTEM] Boot Sequence....................... "
    );

    console_put_string_color(
        &cns,
        " COMPLETE ",
        BLACK,
        LIME
    );

    console_put_string(&cns, "\n");

    console_put_string(
        &cns,
        "[CPU] AMD64 Long Mode........................ "
    );

    console_put_string_color(
        &cns,
        " ONLINE ",
        BLACK,
        GREEN
    );

    console_put_string(&cns, "\n");

    console_put_string(
        &cns,
        "[MEMORY] Physical Memory Manager............. "
    );

    console_put_string_color(
        &cns,
        " READY ",
        BLACK,
        GREEN
    );

    console_put_string(&cns, "\n");

    console_put_string(
        &cns,
        "[VIDEO] GOP Framebuffer...................... "
    );

    console_put_string_color(
        &cns,
        " ACTIVE ",
        BLACK,
        CYAN
    );

    console_put_string(&cns, "\n");

    console_put_string(
        &cns,
        "[VIDEO] Console Driver....................... "
    );

    console_put_string_color(
        &cns,
        " LOADED ",
        BLACK,
        CYAN
    );

    console_put_string(&cns, "\n");

    console_put_string(
        &cns,
        "[SECURITY] Kernel Lockdown................... "
    );

    console_put_string_color(
        &cns,
        " ENABLED ",
        BLACK,
        GREEN
    );

    console_put_string(&cns, "\n\n");

    console_put_string_color(
        &cns,
        "====================== MISSILE CONTROL ======================\n",
        BLACK,
        YELLOW
    );

    console_put_string(&cns, "SILO-01  STATUS ");

    console_put_string_color(
        &cns,
        " ARMED ",
        WHITE,
        RED
    );

    console_put_string(
        &cns,
        "   TARGET LOCK "
    );

    console_put_string_color(
        &cns,
        " YES ",
        BLACK,
        GREEN
    );

    console_put_string(&cns, "\n");

    console_put_string(&cns, "SILO-02  STATUS ");

    console_put_string_color(
        &cns,
        " STANDBY ",
        BLACK,
        YELLOW
    );

    console_put_string(
        &cns,
        " TARGET LOCK "
    );

    console_put_string_color(
        &cns,
        " NO ",
        WHITE,
        RED
    );

    console_put_string(&cns, "\n");

    console_put_string(&cns, "SILO-03  STATUS ");

    console_put_string_color(
        &cns,
        " OFFLINE ",
        BLACK,
        GRAY
    );

    console_put_string(
        &cns,
        " TARGET LOCK "
    );

    console_put_string_color(
        &cns,
        " --- ",
        BLACK,
        GRAY
    );

    console_put_string(&cns, "\n");

    console_put_string(&cns, "SILO-04  STATUS ");

    console_put_string_color(
        &cns,
        " READY ",
        BLACK,
        LIME
    );

    console_put_string(
        &cns,
        "   TARGET LOCK "
    );

    console_put_string_color(
        &cns,
        " YES ",
        BLACK,
        GREEN
    );

    console_put_string(&cns, "\n\n");

    console_put_string_color(
        &cns,
        "======================== LIVE EVENTS ========================\n",
        BLACK,
        BLUE
    );

    console_put_string(&cns, "[00:00:01] UEFI GOP initialized\n");
    console_put_string(&cns, "[00:00:02] ELF kernel loaded\n");
    console_put_string(&cns, "[00:00:03] Framebuffer mapped\n");
    console_put_string(&cns, "[00:00:04] Console initialized\n");
    console_put_string(&cns, "[00:00:05] Video diagnostics complete\n");
    console_put_string(&cns, "[00:00:06] Awaiting launch authorization...\n\n");

    console_put_string(&cns, "AUTHORIZATION ");

    console_put_string_color(
        &cns,
        " DENIED ",
        WHITE,
        RED
    );

    console_put_string(&cns, "\n");

    console_put_string(&cns, "REASON        ");

    console_put_string_color(
        &cns,
        " DEVELOPMENT BUILD ",
        BLACK,
        MAGENTA
    );

    console_put_string(&cns, "\n\n");

    console_put_string_color(
        &cns,
        "==================== ALL SYSTEMS NOMINAL ====================\n\n",
        BLACK,
        LIME
    );


    /*
     * ============================================================
     * SCROLLING STRESS TEST
     * ============================================================
     *
     * This deliberately writes more lines than the visible
     * console can hold.
     *
     * Watch the line numbers at the bottom of the screen.
     */

    console_put_string_color(
        &cns,
        "====================== SCROLL TEST ==========================\n",
        BLACK,
        YELLOW
    );

    for (uint32_t i = 0; i < 100; i++) {

        console_put_string(&cns, "[SCROLL TEST] Line ");

        console_put_uint(i);

        if (i % 2 == 0) {
            console_put_string_color(
                &cns,
                " EVEN ",
                BLACK,
                CYAN
            );
        }
        else {
            console_put_string_color(
                &cns,
                " ODD ",
                BLACK,
                GREEN
            );
        }

        console_put_string(
            &cns,
            " -- The quick brown fox jumps over the lazy dog.\n"
        );
    }


    /*
     * Stay alive.
     */

    while (1) {
        __asm__ volatile("hlt");
    }
}