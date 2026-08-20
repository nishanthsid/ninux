#include <lib/printk.h>
#include <console/kernc.h>
#include <console/console.h>

console *printk_console;

char pk_buff[PK_BUFF_SIZE + 1];
uint32_t index = 0;

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

void printk(const char * fmt, ...){
    // Testing just for simple string cases
    push_str(fmt);
    flush_printk();
}