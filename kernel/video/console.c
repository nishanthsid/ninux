#include <video/console.h>
#include <video/framebuffer.h>
#include <video/fonts8x16.h>
#include <video/color.h>

static uint32_t CUR_X = 0;
static uint32_t CUR_Y = 0;
static uint32_t LINE_WIDTH = 0;
static uint32_t LINE_HEIGHT = 0;
static Color FG = WHITE;
static Color BG = BLACK;

void console_init(){
    uint32_t height = fb_get_height();
    uint32_t width = fb_get_width();

    LINE_WIDTH = width / FONT_WIDTH;
    LINE_HEIGHT = height / FONT_HEIGHT;
}

void console_set_fg(Color fg){
    FG = fg;
}

void console_set_bg(Color bg){
    BG = bg;
}

static void put_char_helper(char c, Color fg, Color bg){
    uint32_t cur_x_advance = 1;
    if(c == '\n'){
        CUR_Y++;
        CUR_X = 0;
        return;
    }
    else if(c == '\t'){
        cur_x_advance = 4;
    }
    else{
        uint32_t pixel_x = CUR_X * FONT_WIDTH;
        uint32_t pixel_y = CUR_Y * FONT_HEIGHT;

        const uint8_t *font = &FONT_8X16[(uint8_t)c*FONT_HEIGHT];

        for(uint8_t i = 0; i < FONT_HEIGHT ;i++){
            uint8_t val = font[i];
            for(uint8_t j = 0; j < FONT_WIDTH;j++){
                if(val & 0x80){
                    fb_put_pixel(pixel_x + j, pixel_y + i, fg);
                }
                else{
                    fb_put_pixel(pixel_x + j, pixel_y + i, bg);
                }
                val <<= 1;
            }
            
        }
    }
    CUR_X += cur_x_advance;
    if(CUR_X >= LINE_WIDTH){
        CUR_X %= LINE_WIDTH;
        CUR_Y++;
    }
}

void console_put_char(char c){
    put_char_helper(c, FG, BG);
}

void console_put_char_color(char c, Color fg, Color bg){
    put_char_helper(c, fg, bg);
}

void console_put_string(const char * string){
    uint32_t i = 0;
    while(string[i] != 0){
        console_put_char(string[i]);
        i++;
    }
}


void console_put_string_color(const char * string, Color fg, Color bg){
    uint32_t i = 0;
    while(string[i] != 0){
        console_put_char_color(string[i], fg, bg);
        i++;
    }
}
