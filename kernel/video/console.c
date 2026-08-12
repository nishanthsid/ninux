#include <video/console.h>
#include <video/framebuffer.h>
#include <video/fonts8x16.h>
#include <video/color.h>
#include <lib/memshift.h>
#include <video/textbuffer.h>

static uint32_t LINE_WIDTH = 0;
static uint32_t LINE_HEIGHT = 0;

void console_sys_init(){
    uint32_t height = fb_get_height();
    uint32_t width = fb_get_width();

    LINE_WIDTH = width / FONT_WIDTH;
    LINE_HEIGHT = height / FONT_HEIGHT;
}

void console_init(console *cns, text_buffer *tb, color24 fg, color24 bg){
    cns->tb = tb;
    cns->cursor_x = 0;
    cns->cursor_y = 0;
    cns->scroll_offset = 0;
    cns->default_bg = bg;
    cns->default_fg = fg;
}

uint32_t console_get_line_height(){
    return LINE_HEIGHT;
}

uint32_t console_get_line_width(){
    return LINE_WIDTH;
}


static inline void console_render_raw(uint32_t port_x, uint32_t port_y, char c, color24 fg, color24 bg){
    
    uint32_t pixel_x = port_x* FONT_WIDTH;
    uint32_t pixel_y = port_y * FONT_HEIGHT;
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

static inline void console_render_char(console *cns){
    uint32_t port_y = cns->scroll_offset + cns->cursor_y;
    uint32_t port_x = cns->cursor_x;
    cell * cl = tb_getcell(cns->tb, cns->scroll_offset + cns->cursor_y, cns->cursor_x);
    console_render_raw(port_x, port_y,cl->c,cl->fg, cl->bg);
}




static void put_char_helper(console *cns, char c, color24 fg, color24 bg){
    text_buffer *tb = cns->tb;

    uint32_t cur_x_advance = 1;
    if(c == '\n'){
        cns->cursor_y++;
        cns->cursor_x= 0;
        cur_x_advance = 0;
    }
    else if(c == '\t'){
        cur_x_advance = 4;
    }
    else{
        tb_putchar(tb, cns->cursor_y + cns->scroll_offset, cns->cursor_x, c, fg, bg);
        console_render_char(cns);
    }
    cns->cursor_x+= cur_x_advance;
    if(cns->cursor_x>= LINE_WIDTH){
        cns->cursor_x%= LINE_WIDTH;
        cns->cursor_y++;
    }

    if(cns->scroll_offset + cns->cursor_y >= tb->rows){
        mem_shift(cns->tb, tb->capacity*sizeof(cell), SHIFT_LEFT, (cns->scroll_offset + cns->cursor_y - tb->rows) * tb->cols*sizeof(cell));
        cns->cursor_y = LINE_HEIGHT - 1;
    }
    else if(cns->cursor_y >= LINE_HEIGHT){
        cns->scroll_offset += (cns->cursor_y - LINE_HEIGHT);
        cns->cursor_y = LINE_HEIGHT - 1;
    }
}


void console_put_char(console *cns, char c){
    put_char_helper(cns, c, cns->default_fg, cns->default_bg);
}

void console_put_char_color(console *cns, char c, color24 fg, color24 bg){
    put_char_helper(cns, c, fg, bg);
}

void console_put_string_color(console *cns, const char * string, color24 fg, color24 bg){
    uint32_t index = 0;
    while(string[index] != 0){
        console_put_char_color(cns, string[index], fg, bg);
        index++;
    }
}

void console_put_string(console *cns, const char * string){
    console_put_string_color(cns, string, cns->default_fg, cns->default_bg);
}

void console_scroll_to(console *cns, uint32_t row){
    cns->scroll_offset = row;
}

void console_fill_color(console *cns, char c, color24 fg, color24 bg){
    for(uint32_t y = 0; y < LINE_HEIGHT;y++){
        for(uint32_t x = 0; x < LINE_WIDTH;x++){
            console_render_raw(x, y, c, fg, bg);
        }
    }
}

void console_fill(console *cns, char c){
    console_fill_color(cns, c, cns->default_fg, cns->default_bg);
}

void console_clear(console *cns){
    console_fill(cns, ' ');
}




