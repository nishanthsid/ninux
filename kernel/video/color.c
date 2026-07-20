#include <video/color.h>

uint32_t get_pixel_value(Color color){
    return color.red << 16 | color.green << 8 | color.blue;
}

Color color_rgb(uint8_t red, uint8_t green, uint8_t blue){
    return (Color){red, green, blue};
}