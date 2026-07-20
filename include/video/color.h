#ifndef COLOR_H
#define COLOR_H

#include <types.h>

typedef struct __attribute__((packed)){
    
    uint8_t red;
    uint8_t green;
    uint8_t blue;

} Color;

uint32_t get_pixel_value(Color color);
Color color_rgb(uint8_t, uint8_t, uint8_t);


#define BLACK        ((Color){  0,   0,   0})
#define WHITE        ((Color){255, 255, 255})

#define RED          ((Color){255,   0,   0})
#define GREEN        ((Color){  0, 255,   0})
#define BLUE         ((Color){  0,   0, 255})

#define YELLOW       ((Color){255, 255,   0})
#define CYAN         ((Color){  0, 255, 255})
#define MAGENTA      ((Color){255,   0, 255})

#define ORANGE       ((Color){255, 165,   0})
#define PURPLE       ((Color){128,   0, 128})
#define PINK         ((Color){255, 192, 203})

#define BROWN        ((Color){139,  69,  19})
#define GRAY         ((Color){128, 128, 128})
#define LIGHT_GRAY   ((Color){211, 211, 211})
#define DARK_GRAY    ((Color){ 64,  64,  64})

#define LIME         ((Color){ 50, 205,  50})
#define NAVY         ((Color){  0,   0, 128})
#define TEAL         ((Color){  0, 128, 128})
#define OLIVE        ((Color){128, 128,   0})
#define MAROON       ((Color){128,   0,   0})
#define SILVER       ((Color){192, 192, 192})

#endif