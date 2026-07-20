#!/bin/bash
set -e

echo "Cleaning..."
rm -rf build esp
mkdir -p build
mkdir -p build/kernel/video
mkdir -p esp/EFI/BOOT

echo "[1/6] Compiling bootloader..."

gcc \
    -I/usr/include/efi \
    -I/usr/include/efi/x86_64 \
    -Iinclude \
    -fpic \
    -fshort-wchar \
    -ffreestanding \
    -fno-stack-protector \
    -fno-stack-check \
    -mno-red-zone \
    -Wall \
    -Wextra \
    -c boot/main.c \
    -o build/main.o

echo "[2/6] Linking bootloader..."

ld \
    -nostdlib \
    -znocombreloc \
    -T /usr/lib/elf_x86_64_efi.lds \
    -shared \
    -Bsymbolic \
    /usr/lib/crt0-efi-x86_64.o \
    build/main.o \
    --start-group \
    -L/usr/lib \
    -lefi \
    -lgnuefi \
    --end-group \
    -o build/main.so

echo "[3/6] Creating EFI executable..."

objcopy \
    -j .text \
    -j .sdata \
    -j .data \
    -j .rodata \
    -j .dynamic \
    -j .dynsym \
    -j .rel \
    -j .rela \
    -j .reloc \
    -j .eh_frame \
    --target=efi-app-x86_64 \
    build/main.so \
    esp/EFI/BOOT/BOOTX64.EFI

echo "[4/6] Building kernel..."

gcc \
    -c \
    -Iinclude \
    -ffreestanding \
    -mno-red-zone \
    -Wall \
    -Wextra \
    kernel/kernel.c \
    -o build/kernel/kernel.o

gcc \
    -c \
    -Iinclude \
    -ffreestanding \
    -mno-red-zone \
    -Wall \
    -Wextra \
    kernel/video/framebuffer.c \
    -o build/kernel/video/framebuffer.o

gcc \
    -c \
    -Iinclude \
    -ffreestanding \
    -mno-red-zone \
    -Wall \
    -Wextra \
    kernel/video/console.c \
    -o build/kernel/video/console.o

gcc \
    -c \
    -Iinclude \
    -ffreestanding \
    -mno-red-zone \
    -Wall \
    -Wextra \
    kernel/video/color.c \
    -o build/kernel/video/color.o

gcc \
    -c \
    -Iinclude \
    -ffreestanding \
    -mno-red-zone \
    -Wall \
    -Wextra \
    kernel/video/fonts8x16.c \
    -o build/kernel/video/fonts8x16.o

ld \
    -T kernel/linker.ld \
    -o build/kernel.elf \
    build/kernel/kernel.o \
    build/kernel/video/framebuffer.o \
    build/kernel/video/console.o \
    build/kernel/video/color.o \
    build/kernel/video/fonts8x16.o

cp build/kernel.elf esp/EFI/BOOT/kernel.elf

echo
echo "Bootloader:"
file esp/EFI/BOOT/BOOTX64.EFI

echo
echo "Kernel:"
file esp/EFI/BOOT/kernel.elf
echo

echo "[5/6] Preparing OVMF..."

cp /usr/share/OVMF/OVMF_VARS_4M.fd build/OVMF_VARS.fd

echo "[6/6] Starting QEMU..."

qemu-system-x86_64 \
    -machine q35 \
    -m 512M \
    -drive if=pflash,format=raw,readonly=on,file=/usr/share/OVMF/OVMF_CODE_4M.fd \
    -drive if=pflash,format=raw,file=build/OVMF_VARS.fd \
    -drive format=raw,file=fat:rw:esp \
    -serial stdio \
    -monitor none