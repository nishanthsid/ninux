#include <boot.h>
#include <types.h>

void kernel_main(BootInfo *Boot)
{
    uint32_t *fb = (uint32_t *)Boot->FramebufferBase;

    uint32_t width  = Boot->Width;
    uint32_t height = Boot->Height;

    uint32_t TILE_SIZE = 64;

    uint32_t clr1 = 0;
    uint32_t clr2 = 255;
    uint32_t cl1 = 0;
    uint32_t cl2 = 255;

    int32_t add = 1;

    while (1){
        clr1++;
        clr1 %= 255;
        clr2 = 255 - clr1;
        cl1 = clr1;
        cl2 = clr2;
        TILE_SIZE += add;
        
        if(TILE_SIZE > 64){
            add = -1;
            TILE_SIZE = 64;
        }
        if(TILE_SIZE == 0){
            add = 1;
            TILE_SIZE = 1;
        }

        cl1 |= clr1<<8 | clr1<<16;
        cl2 |= clr2<<8 | clr2<<16;

        for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {

            uint32_t tileX = x / TILE_SIZE;
            uint32_t tileY = y / TILE_SIZE;

            if ((tileX + tileY) % 2 == 0)
                fb[y * width + x] = cl1;
            else
                fb[y * width + x] = cl2;
        }
    }
    }
}