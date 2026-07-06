#ifndef BOOT_H
#define BOOT_H

#include <types.h>

typedef struct {
    void   *FramebufferBase;
    uintptr_t   FramebufferSize;
    uint32_t  Width;
    uint32_t  Height;
    uint32_t  PixelsPerScanLine;
} BootInfo;

#endif