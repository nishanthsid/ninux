#ifndef PRINTK_H
#define PRINTK_H
#include <stdarg.h>

#define PK_BUFF_SIZE 4096

void init_printk();
void printk(const char * fmt, ...);
void flush_printk();

#endif