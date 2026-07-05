#ifndef BOOT_H
#define BOOT_H

#include <efi.h>

typedef struct {
    VOID   *FramebufferBase;
    UINTN   FramebufferSize;
    UINT32  Width;
    UINT32  Height;
    UINT32  PixelsPerScanLine;
} BootInfo;

#endif