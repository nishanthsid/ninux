#ifndef FRAME_BUFF_H
#define FRAME_BUFF_H

#include <types.h>
#include <boot.h>
#include <video/color.h>

void framebuffer_init(BootInfo * boot_info);

uint32_t fb_get_width(void);
uint32_t fb_get_height(void);

void fb_put_pixel(uint32_t x, uint32_t y , Color color);
void fb_fill(Color color);

#endif