#include <video/color.h>
#include <video/framebuffer.h>

#include <boot.h>
#include <lib/memshift.h>

static uint32_t *FB_BASE = NULL;
static uint32_t WIDTH = 0;
static uint32_t HEIGHT = 0;
static uint32_t PIXEL_PER_SCAN_LINE = 0;
static uintptr_t FRAME_BUFFER_SIZE = 0;

void framebuffer_init(BootInfo *boot_info){
    FB_BASE = boot_info->FramebufferBase;
    WIDTH = boot_info->Width;
    HEIGHT = boot_info->Height;
    PIXEL_PER_SCAN_LINE = boot_info->PixelsPerScanLine;
    FRAME_BUFFER_SIZE = boot_info->FramebufferSize;
}

uint32_t fb_get_height(){
    return HEIGHT;
}

uint32_t fb_get_width(){
    return WIDTH;
}

void fb_put_pixel(uint32_t x, uint32_t y, Color color){
    if (x >= WIDTH || y >= HEIGHT){
        return;
    }
    FB_BASE[y*PIXEL_PER_SCAN_LINE + x] = get_pixel_value(color);
}

void fb_shift_buffer(uint8_t shift_direction, uint32_t shift_postitions){
    uint32_t bytes = shift_postitions * PIXEL_PER_SCAN_LINE * sizeof(uint32_t);
    mem_shift(FB_BASE, FRAME_BUFFER_SIZE, shift_direction, bytes);
}

void fb_fill(Color color){
    uint32_t pixel = get_pixel_value(color);
    for(uint32_t i = 0; i < WIDTH;i++){
        for(uint32_t j = 0; j < HEIGHT;j++){
            FB_BASE[j*PIXEL_PER_SCAN_LINE + i] = pixel;
        }
    }
}