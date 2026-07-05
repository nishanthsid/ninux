#include <efi.h>
#include <efilib.h>
#include <elf.h>

EFI_STATUS Status;
EFI_LOADED_IMAGE *LoadedImage;
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem;
EFI_FILE_PROTOCOL *Root;
EFI_FILE_PROTOCOL *KernelFile;
Elf64_Ehdr KernelHeader;
Elf64_Phdr *ProgramHeaders;
BOOLEAN IsDebug = FALSE;

EFI_STATUS load_kernel(EFI_HANDLE ImageHandle){
    
    //First get the Handle for the device from which this program loaded 
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

    //Get the file system handle from the device that we read
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

    //Get the handle for the root of the filesystem from the file system handle we read
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

    //Read the actual kernel file into its own handle, right now, the path is hardcoded and assumed to be in
    //the location EFI\BOOT\Kernel.elf
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

    return EFI_SUCCESS;
}

EFI_STATUS read_elf_header(BOOLEAN IsDebug){
    UINTN Size = sizeof(Elf64_Ehdr);
    //Read the ELF headers from the file, the size of the read is coming from the size of the
    //ELF header defined in elf.h
    Status = uefi_call_wrapper(
        KernelFile->Read,
        3,
        KernelFile,
        &Size,
        &KernelHeader
    );

    if(EFI_ERROR(Status)){
        Print(L"Failed to read the kernel header, EXITING\n");
        return Status;
    }

    if (Size != sizeof(Elf64_Ehdr)) {
        Print(L"Incomplete ELF header\n");
        return EFI_LOAD_ERROR;
    }

    if(IsDebug){
        Print(L"Debug information about the ELF header\n");
        Print(L"Entry: %lx\n", KernelHeader.e_entry);
        Print(L"Program Header Offset: %lx\n", KernelHeader.e_phoff);
        Print(L"Program Header Count: %d\n", KernelHeader.e_phnum);
        Print(L"Program Header Size: %d\n", KernelHeader.e_phentsize);
    }

    //Check the header for the ELF magic

    if(KernelHeader.e_ident[EI_MAG0] != ELFMAG0 ||
       KernelHeader.e_ident[EI_MAG1] != ELFMAG1 ||
       KernelHeader.e_ident[EI_MAG2] != ELFMAG2 ||
       KernelHeader.e_ident[EI_MAG3] != ELFMAG3
    ){
        Print(L"Kernel is not a valid ELF file, EXITING\n");
        return EFI_LOAD_ERROR;
    }

    //Check architecture, endianess and bitlength
    if(KernelHeader.e_ident[EI_CLASS] != ELFCLASS64 ||
       KernelHeader.e_ident[EI_DATA]  != ELFDATA2LSB ||
       KernelHeader.e_machine != EM_X86_64){
            Print(L"Unsupported kernel, EXITING\n");
            return EFI_LOAD_ERROR;
       }

    Print(L"Kernel ELF header successfully checked, no issues reported\n");
    return EFI_SUCCESS;
}

EFI_STATUS read_program_headers(BOOLEAN IsDebug){
    
    UINTN Size;
    
    if (KernelHeader.e_phentsize != sizeof(Elf64_Phdr)) {
        Print(L"Unexpected Program Header size\n");
        return EFI_LOAD_ERROR;
    }

    //Seek to the program header section
    Status = uefi_call_wrapper(
        KernelFile->SetPosition,
        2,
        KernelFile,
        KernelHeader.e_phoff //Offset to program header
    );

    if(EFI_ERROR(Status)){
        Print(L"Error seeking the program header section in kernel header, EXITING\n");
        return Status;
    }

    //Allocate memory to all the program headers

    //Calculate the size needed
    Size = KernelHeader.e_phnum * KernelHeader.e_phentsize;

    //Allocate the memory now

    Status = uefi_call_wrapper(
        BS->AllocatePool,
        3,
        EfiLoaderData,
        Size,
        (VOID **)&ProgramHeaders
    );

    if(EFI_ERROR(Status)){
        Print(L"Error Allocation memory pool for the program header sections, EXITING\n");
        return Status;
    }

    //Read the program header section to ProgramHeaders array now

    Status = uefi_call_wrapper(
        KernelFile->Read,
        3,
        KernelFile,
        &Size,
        ProgramHeaders
    );

    if(EFI_ERROR(Status)){
        Print(L"Error reading the program header sections, EXITING\n");
        return Status;
    }

    if (Size != KernelHeader.e_phnum * sizeof(Elf64_Phdr)) {
        Print(L"Incomplete Program Header Table\n");
        return EFI_LOAD_ERROR;
    }

    if(IsDebug){
        for(UINTN i = 0; i < KernelHeader.e_phnum;i++){
            Print(L"\nProgram Header %d\n", i);
            Print(L"Type      : %x\n", ProgramHeaders[i].p_type);
            Print(L"Offset    : %lx\n", ProgramHeaders[i].p_offset);
            Print(L"VAddr     : %lx\n", ProgramHeaders[i].p_vaddr);
            Print(L"File Size : %lx\n", ProgramHeaders[i].p_filesz);
            Print(L"Mem Size  : %lx\n", ProgramHeaders[i].p_memsz);
            Print(L"Flags     : %x\n", ProgramHeaders[i].p_flags);
        }
    }

    Print(L"Kernel program header sections successfully loaded, no issues reported\n");
    return EFI_SUCCESS;

}

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable){
    
    InitializeLib(ImageHandle, SystemTable);
    
    //Load the kernel into a file handle
    Status = load_kernel(ImageHandle);
    if(EFI_ERROR(Status)) return Status;
    
    //Read the file handle to check if kernel is a valid 
    Status = read_elf_header(IsDebug);
    if(EFI_ERROR(Status)) return Status;

    //Read and store the program header sections 
    Status = read_program_headers(IsDebug);
    if(EFI_ERROR(Status)) return Status;
    
    //Simple halt
    while (1);
    
    return EFI_SUCCESS;
}