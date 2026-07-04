#include <efi.h>
#include <efilib.h>

EFI_STATUS EFIAPI
efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);

    EFI_STATUS Status;

    EFI_LOADED_IMAGE *LoadedImage;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem;
    EFI_FILE_PROTOCOL *Root;
    EFI_FILE_PROTOCOL *KernelFile;

    //
    // Get the Loaded Image Protocol
    //
    Status = uefi_call_wrapper(
        BS->HandleProtocol,
        3,
        ImageHandle,
        &LoadedImageProtocol,
        (VOID **)&LoadedImage
    );

    if (EFI_ERROR(Status)) {
        Print(L"Failed to get LoadedImageProtocol\n");
        return Status;
    }

    //
    // Get the filesystem protocol
    //
    Status = uefi_call_wrapper(
        BS->HandleProtocol,
        3,
        LoadedImage->DeviceHandle,
        &FileSystemProtocol,
        (VOID **)&FileSystem
    );

    if (EFI_ERROR(Status)) {
        Print(L"Failed to get filesystem\n");
        return Status;
    }

    //
    // Open the filesystem root
    //
    Status = uefi_call_wrapper(
        FileSystem->OpenVolume,
        2,
        FileSystem,
        &Root
    );

    if (EFI_ERROR(Status)) {
        Print(L"Failed to open root directory\n");
        return Status;
    }

    //
    // Open kernel.elf
    //
    Status = uefi_call_wrapper(
        Root->Open,
        5,
        Root,
        &KernelFile,
        L"EFI\\BOOT\\kernel.elf",
        EFI_FILE_MODE_READ,
        0
    );

    if (EFI_ERROR(Status)) {
        Print(L"Failed to open kernel.elf\n");
        return Status;
    }

    Print(L"Successfully opened kernel.elf!\n");

    while (1);

    return EFI_SUCCESS;
}