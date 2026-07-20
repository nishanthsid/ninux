#ifndef CONSOLE_H
#define CONSOLE_H

#include <video/color.h>

void console_init(void);
void console_put_char(char c);
void console_put_string(const char * string);
void console_set_fg(Color fg_color);
void console_set_bg(Color bg_color);
void console_put_char_color(char c, Color fg, Color bg);
void console_put_string_color(const char * string, Color fg, Color bg);

#endif