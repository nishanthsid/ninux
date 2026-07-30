#include <video/color.h>

uint32_t get_pixel_value(color24 color){
    return color.red << 16 | color.green << 8 | color.blue;
}

color24 color_rgb(uint8_t red, uint8_t green, uint8_t blue){
    return (color24){red, green, blue};
}