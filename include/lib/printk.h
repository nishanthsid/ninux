#ifndef PRINTK_H
#define PRINTK_H
#include <stdarg.h>
#include <console/kernc.h>
#include <console/console.h>
#include <video/color.h>

#define PK_BUFF_SIZE 4096

void init_printk();
void printk(const char * fmt, ...);
void flush_printk();


void printk_setfg(color24 fg);
void printk_setbg(color24 bg);

void printk_reset_colors();

#endif