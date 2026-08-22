#include <lib/printk.h>
#include <console/kernc.h>
#include <console/console.h>

console *printk_console;

char pk_buff[PK_BUFF_SIZE + 1];
uint32_t index = 0;

typedef enum{
    NORMAL,
    FORMAT_CHECK,
} pkparser_context;

void init_printk(){
    printk_console = get_kernel_console();
    for(uint32_t i = 0;i < PK_BUFF_SIZE;i++){
        pk_buff[i] = 0;
    }
    index = 0;
}

void flush_printk(){
    pk_buff[index] = 0;
    console_put_string(printk_console, pk_buff);
    index = 0;
}

static inline void push_char(char c){
    if(index >= PK_BUFF_SIZE - 1){
        flush_printk();
    }
    pk_buff[index++] = c;
}

static inline void push_str(const char * str){
    uint32_t i = 0;
    while(str[i] != 0){
        if(index >= PK_BUFF_SIZE - 1){
            flush_printk();
        }
        pk_buff[index++] = str[i];
        i++;
    }
}


static void handle_uint(va_list *args){
    uint32_t v = va_arg(*args, uint32_t);
    if (v == 0) {
        push_char('0');
        return;
    }
    char arr[32];
    for(uint32_t i = 0; i < 32;i++) arr[i] = 0;
    uint32_t ind = 0;
    while(v > 0){
        arr[ind] = '0' + v % 10;
        v /= 10;
        ind++;
    }
    ind--;
    uint32_t indl = 0;
    while(indl < ind){
        char c = arr[indl];
        arr[indl] = arr[ind];
        arr[ind] = c;
        indl++;
        ind--;
    }
    push_str(arr);
}

static void handle_int(va_list *args){
    int32_t v = va_arg(*args, int32_t);
    if (v == 0) {
        push_char('0');
        return;
    }
    int32_t is_neg = 0;
    if(v < 0){
        is_neg = 1;
        v *= -1;
    }
    char arr[32];
    for(uint32_t i = 0; i < 32;i++) arr[i] = 0;
    uint32_t ind = 0;
    while(v > 0){
        arr[ind] = '0' + v % 10;
        v /= 10;
        ind++;
    }
    ind--;
    uint32_t indl = 0;
    while(indl < ind){
        char c = arr[indl];
        arr[indl] = arr[ind];
        arr[ind] = c;
        indl++;
        ind--;
    }
    if(is_neg == 1){
        push_char('-');
    }
    push_str(arr);

}

static void handle_hex(va_list *args, uint8_t is_upper){
    uint32_t v = va_arg(*args, uint32_t);
    if (v == 0) {
        push_str("0x0");
        return;
    }
    char arr[32];
    for(uint32_t i = 0; i < 32;i++) arr[i] = 0;
    uint32_t ind = 0;
    while(v > 0){
        char curr = 0;
        int dig = v % 16;
        if(dig <= 9) curr = '0' + dig;
        else curr = ((is_upper == 1)?'A':'a') + dig - 10;
        arr[ind] = curr;
        v /= 16;
        ind++;
    }
    ind--;
    uint32_t indl = 0;
    while(indl < ind){
        char c = arr[indl];
        arr[indl] = arr[ind];
        arr[ind] = c;
        indl++;
        ind--;
    }
    push_str("0x");
    push_str(arr);
}


static void printk_helper(const char* fmt, va_list *args){
    uint32_t index = 0;
    pkparser_context cntx = NORMAL;
    while(fmt[index] != 0){
        char c = fmt[index];
        switch(cntx){
            case NORMAL:{
                if(c == '%'){
                    cntx = FORMAT_CHECK;
                }
                else{
                    push_char(c);
                }
                break;
            }
            case FORMAT_CHECK:{
                switch(c){
                    case '%': {
                        push_char(c);
                        break;
                    }
                    case 'd':{
                        handle_int(args);
                        break;
                    }
                    case 'c':{
                        char c = va_arg(*args, int32_t);
                        push_char(c);
                        break;
                    }
                    case 's':{
                        char * str = va_arg(*args, char *);
                        push_str(str);
                        break;
                    }
                    case 'u':{
                        handle_uint(args);
                        break;
                    }
                    case 'x':{
                        handle_hex(args, 0);
                        break;
                    }
                    case 'X':{
                        handle_hex(args, 1);
                        break;
                    }

                    
                }
                cntx = NORMAL;
            }
        }
        index++;
    }
}

void printk_setfg(color24 fg){
    flush_printk();
    console_set_fg(printk_console, fg);
}
void printk_setbg(color24 bg){
    flush_printk();
    console_set_bg(printk_console, bg);
}

void printk_reset_colors(){
    flush_printk();
    console_reset_colors(printk_console);
}


void printk(const char * fmt, ...){
    va_list args;
    va_start(args, fmt);
    printk_helper(fmt, &args);
    flush_printk();
    va_end(args);
}