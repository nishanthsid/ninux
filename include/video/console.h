#ifndef CONSOLE_H
#define CONSOLE_H

#include <video/color.h>
#include <video/textbuffer.h>
#include <video/textbuffer.h>

void console_init();

typedef struct {
    text_buffer * tb;
    uint32_t cursor_x;
    uint32_t cursor_y;
    uint32_t scroll_offset;

} console;

// Deprecated - Will be removed after Console shifts to using text_buffer
void _console_put_char(char c);
void _console_put_string(const char * string);
void _console_put_char_color(char c, color24 fg, color24 bg);
void _console_put_string_color(const char * string, color24 fg, color24 bg);


#endif