# NINUX

A hobby Unix-like operating system built from scratch in C for the x86-64 architecture.

NINUX is a personal learning project created to explore operating systems from first principles. The goal is not to compete with existing operating systems, but to understand how they work by implementing them piece by piece.

---

## Why NINUX?

NINUX exists because reading operating system textbooks wasn't enough.

I wanted to understand how an operating system actually works by building one—from the firmware interface to memory management, scheduling, filesystems, networking, and user space.

Every subsystem is implemented as a learning exercise with an emphasis on simplicity, readability, and documentation.

---

## Current Progress

### Boot Process

- Boots as a native UEFI application
- Built using GNU-EFI
- Boots directly from QEMU using OVMF
- Successfully transfers control to the kernel entry point

### Boot Information

The bootloader currently passes basic boot information to the kernel, including:

- Framebuffer address
- Framebuffer dimensions
- Pixels per scan line
- Framebuffer size

---

## Project Goals

NINUX aims to implement, from scratch:

- UEFI bootloader
- Physical and virtual memory management
- Paging
- Interrupt handling
- Scheduler
- Processes and threads
- System calls
- Virtual File System (VFS)
- Device drivers
- Networking
- Userspace programs
- Shell

---

## Technologies

- C
- GNU-EFI
- UEFI
- QEMU
- OVMF
- GCC
- Make
- ELF
- x86-64

---

## Repository Structure

```
boot/
    UEFI bootloader

kernel/
    Kernel source

include/
    Shared headers

Build scripts (run.sh)
```

---

## Running

Requirements

- QEMU
- OVMF
- GNU-EFI

Build and Run

```bash
./run.sh
```

---

## Documentation

This project is documented as it evolves.

Topics include:

- UEFI
- Boot process
- Memory management
- Paging
- Kernel architecture
- Device drivers
- Operating system internals

---

## Project Status

🚧 Early development.

The current focus is establishing a solid boot process and kernel architecture before implementing higher-level operating system components.

---
