#include <video/color.h>
#include <video/framebuffer.h>

#include <boot.h>

static uint32_t *FB_BASE = NULL;
static uint32_t WIDTH = 0;
static uint32_t HEIGHT = 0;
static uint32_t PIXEL_PER_SCAN_LINE = 0;

void framebuffer_init(BootInfo *boot_info){
    FB_BASE = boot_info->FramebufferBase;
    WIDTH = boot_info->Width;
    HEIGHT = boot_info->Height;
    PIXEL_PER_SCAN_LINE = boot_info->PixelsPerScanLine;
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

void fb_fill(Color color){
    uint32_t pixel = get_pixel_value(color);
    for(uint32_t i = 0; i < WIDTH;i++){
        for(uint32_t j = 0; j < HEIGHT;j++){
            FB_BASE[j*PIXEL_PER_SCAN_LINE + i] = pixel;
        }
    }
}