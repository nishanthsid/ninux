#include <boot.h>

void kernel_main(BootInfo *Boot)
{
    UINT32 *fb = (UINT32 *)Boot->FramebufferBase;

    UINT32 width  = Boot->Width;
    UINT32 height = Boot->Height;

    const UINT32 TILE_SIZE = 64;

    for (UINT32 y = 0; y < height; y++) {
        for (UINT32 x = 0; x < width; x++) {

            UINT32 tileX = x / TILE_SIZE;
            UINT32 tileY = y / TILE_SIZE;

            if ((tileX + tileY) % 2 == 0)
                fb[y * width + x] = 0x00FFFFFF; // White
            else
                fb[y * width + x] = 0x00000000; // Black
        }
    }

    while (1);
}