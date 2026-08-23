#ifndef COLOR_H
#define COLOR_H

#include <types.h>

typedef struct __attribute__((packed)){
    
    uint8_t red;
    uint8_t green;
    uint8_t blue;

} color24;

uint32_t get_pixel_value(color24 color);
color24 color_rgb(uint8_t, uint8_t, uint8_t);


#define BLACK        ((color24){  0,   0,   0})
#define WHITE        ((color24){255, 255, 255})

#define RED          ((color24){255,   0,   0})
#define GREEN        ((color24){  0, 255,   0})
#define BLUE         ((color24){  0,   0, 255})

#define YELLOW       ((color24){255, 255,   0})
#define CYAN         ((color24){  0, 255, 255})
#define MAGENTA      ((color24){255,   0, 255})

#define ORANGE       ((color24){255, 165,   0})
#define PURPLE       ((color24){128,   0, 128})
#define PINK         ((color24){255, 192, 203})

#define BROWN        ((color24){139,  69,  19})
#define GRAY         ((color24){128, 128, 128})
#define LIGHT_GRAY   ((color24){211, 211, 211})
#define DARK_GRAY    ((color24){ 64,  64,  64})

#define LIME         ((color24){ 50, 205,  50})
#define NAVY         ((color24){  0,   0, 128})
#define TEAL         ((color24){  0, 128, 128})
#define OLIVE        ((color24){128, 128,   0})
#define MAROON       ((color24){128,   0,   0})
#define SILVER       ((color24){192, 192, 192})

#define DEFAULT_FG   ((color24){  0, 255,   0})
#define DEFAULT_BG   ((color24){  0, 0,   0})

#endif