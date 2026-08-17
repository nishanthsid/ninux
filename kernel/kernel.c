#include <boot.h>
#include <types.h>
#include <video/framebuffer.h>
#include <video/console.h>
#include <video/textbuffer.h>
#include <video/color.h>

#define TB_MAX_ROWS 512
#define TB_MAX_COLS 160

static cell console_cells[TB_MAX_ROWS * TB_MAX_COLS];

static text_buffer tb;
static console cns;


/*
 * ============================================================
 * Simple pseudo-random number generator
 * ============================================================
 */

static uint32_t rng_state = 0x12345678;

static uint32_t random_u32()
{
    rng_state = rng_state * 1664525u + 1013904223u;
    return rng_state;
}

static uint32_t random_range(uint32_t min, uint32_t max)
{
    return min + (random_u32() % (max - min + 1));
}


/*
 * ============================================================
 * Integer printing
 * ============================================================
 */

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


/*
 * ============================================================
 * Small delay
 * ============================================================
 */

static void delay()
{
    for (volatile uint32_t i = 0; i < 8000000; i++) {
        __asm__ volatile("" ::: "memory");
    }
}


/*
 * ============================================================
 * Kernel
 * ============================================================
 */

void kernel_main(BootInfo *Boot)
{
    framebuffer_init(Boot);

    console_sys_init();

    fb_fill(BLACK);


    /*
     * --------------------------------------------------------
     * Console dimensions
     * --------------------------------------------------------
     */

    uint32_t screen_rows = console_get_line_height();
    uint32_t screen_cols = console_get_line_width();


    /*
     * --------------------------------------------------------
     * Text buffer
     * --------------------------------------------------------
     */

    tb_init(
        &tb,
        console_cells,
        TB_MAX_ROWS,
        TB_MAX_COLS,
        WHITE,
        BLACK
    );


    /*
     * --------------------------------------------------------
     * Console
     * --------------------------------------------------------
     */

    console_init(
        &cns,
        &tb,
        WHITE,
        BLACK
    );


    /*
     * ========================================================
     * BOOT SCREEN
     * ========================================================
     */

    console_put_string_color(
        &cns,
        "==========================================================================\n",
        BLACK,
        CYAN
    );

    console_put_string_color(
        &cns,
        "              NINUX STRATEGIC COMMAND TERMINAL v0.1                    \n",
        BLACK,
        CYAN
    );

    console_put_string_color(
        &cns,
        "==========================================================================\n\n",
        BLACK,
        CYAN
    );


    /*
     * --------------------------------------------------------
     * System status
     * --------------------------------------------------------
     */

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


    /*
     * ========================================================
     * MISSILE CONTROL
     * ========================================================
     */

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


    /*
     * ========================================================
     * LIVE EVENTS
     * ========================================================
     */

    console_put_string_color(
        &cns,
        "======================== LIVE EVENTS ========================\n",
        BLACK,
        BLUE
    );

    console_put_string(
        &cns,
        "[00:00:01] UEFI GOP initialized\n"
    );

    console_put_string(
        &cns,
        "[00:00:02] ELF kernel loaded\n"
    );

    console_put_string(
        &cns,
        "[00:00:03] Framebuffer mapped\n"
    );

    console_put_string(
        &cns,
        "[00:00:04] Console initialized\n"
    );

    console_put_string(
        &cns,
        "[00:00:05] Video diagnostics complete\n"
    );

    console_put_string(
        &cns,
        "[00:00:06] Awaiting launch authorization...\n\n"
    );


    console_put_string(&cns, "AUTHORIZATION ");

    console_put_string_color(
        &cns,
        " DENIED ",
        WHITE,
        RED
    );

    console_put_string(&cns, "\n");


    console_put_string(
        &cns,
        "REASON        "
    );

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
     * ========================================================
     * AUTOMATIC SCROLL TEST
     * ========================================================
     */

    console_put_string_color(
        &cns,
        "====================== SCROLL TEST ==========================\n",
        BLACK,
        YELLOW
    );


    for (uint32_t i = 0; i < 300; i++) {

        console_put_string(
            &cns,
            "[SCROLL TEST] Line "
        );

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
     * ========================================================
     * RANDOM SCROLL TEST
     * ========================================================
     *
     * ONLY test scrolling between:
     *
     *     row 0
     *     row 1
     *
     * This makes it very obvious whether moving the viewport
     * by exactly one row works correctly.
     */

    console_put_string_color(
        &cns,
        "\n====================== RANDOM SCROLL =======================\n",
        BLACK,
        MAGENTA
    );

    delay();


    for (uint32_t i = 0; i < 30; i++) {

        /*
         * Randomly choose:
         *
         *     0 = normal viewport
         *     1 = shifted down by one row
         */

        uint32_t row = random_u32() % 2;

        console_scroll_to(
            &cns,
            row
        );

        delay();
    }


    /*
     * ========================================================
     * RETURN TO TOP
     * ========================================================
     */

    console_scroll_to(
        &cns,
        0
    );


    delay();


    /*
     * ========================================================
     * RETURN TO LIVE / BOTTOM
     * ========================================================
     */

    uint32_t bottom_row = 0;

    if (TB_MAX_ROWS > screen_rows) {
        bottom_row = TB_MAX_ROWS - screen_rows;
    }

    console_scroll_to(
        &cns,
        bottom_row
    );


    delay();


    /*
     * ========================================================
     * LIVE OUTPUT
     * ========================================================
     */

    console_put_string_color(
        &cns,
        "======================== LIVE MODE =========================\n",
        BLACK,
        LIME
    );


    for (uint32_t i = 0; i < 50; i++) {

        console_put_string(
            &cns,
            "[LIVE] Event "
        );

        console_put_uint(i);

        console_put_string(
            &cns,
            " -- system operating normally\n"
        );

        delay();
    }


    /*
     * ========================================================
     * FINAL STATE
     * ========================================================
     */

    console_put_string_color(
        &cns,
        "\n==================== ALL SYSTEMS NOMINAL ====================\n",
        BLACK,
        LIME
    );


    /*
     * Stay alive.
     */

    while (1) {
        __asm__ volatile("hlt");
    }
}