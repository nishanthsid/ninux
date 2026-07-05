#include <boot.h>

void kernel_main(BootInfo *Boot)
{
    UINT32 *fb = (UINT32 *)Boot->FramebufferBase;

    UINT32 width  = Boot->Width;
    UINT32 height = Boot->Height;

    UINT32 TILE_SIZE = 64;

    UINT32 clr1 = 0;
    UINT32 clr2 = 255;
    UINT32 cl1 = 0;
    UINT32 cl2 = 255;

    INT32 add = 1;

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

        for (UINT32 y = 0; y < height; y++) {
        for (UINT32 x = 0; x < width; x++) {

            UINT32 tileX = x / TILE_SIZE;
            UINT32 tileY = y / TILE_SIZE;

            if ((tileX + tileY) % 2 == 0)
                fb[y * width + x] = cl1;
            else
                fb[y * width + x] = cl2;
        }
    }
    }
}