#ifndef CONSOLE_H
#define CONSOLE_H

#include <video/color.h>
#include <video/textbuffer.h>


void console_init();

// Deprecated - Will be removed after Console shits to using TextBuffer
void _console_put_char(char c);
void _console_put_string(const char * string);
void _console_put_char_color(char c, Color fg, Color bg);
void _console_put_string_color(const char * string, Color fg, Color bg);

void console_put_char(TextBuffer *tb, char c);
void console_put_string(TextBuffer *tb, const char * string);
void console_put_char_color(TextBuffer *tb, char c, Color fg, Color bg);
void console_put_string_color(TextBuffer *tb, const char * string, Color fg, Color bg);


#endif