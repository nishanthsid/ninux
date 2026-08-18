#ifndef CONSOLE_H
#define CONSOLE_H

#include <video/color.h>
#include <console/textbuffer.h>



typedef struct {
    text_buffer * tb;
    uint32_t cursor_x;
    uint32_t cursor_y;
    uint32_t scroll_offset;
    color24 default_fg;
    color24 default_bg;
} console;

void console_sys_init();

void console_init(console * cns, text_buffer *tb, color24 bg, color24 fg);

uint32_t console_get_line_height();
uint32_t console_get_line_width();

void console_put_char(console *cns, char c);
void console_put_string(console *cns, const char * string);
void console_put_char_color(console *cns, char c, color24 fg, color24 bg);
void console_put_string_color(console *cns, const char * string, color24 fg, color24 bg);

void console_scroll_to(console *cns, uint32_t row);
void console_clear(console *cns);
void console_fill(console *cns, char c);
void console_fill_color(console *cns, char c, color24 fg, color24 bg);


#endif