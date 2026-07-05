#include <efi.h>
#include <efilib.h>
#include <elf.h>
#include <config.h>
#include <boot.h>

typedef void (*KernelEntry)(BootInfo *);

EFI_STATUS Status;
EFI_LOADED_IMAGE *LoadedImage;
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem;
EFI_FILE_PROTOCOL *Root;
EFI_FILE_PROTOCOL *KernelFile;
Elf64_Ehdr KernelHeader;
Elf64_Phdr *ProgramHeaders;
BOOLEAN IsDebug = FALSE;
BootInfo Boot;
EFI_MEMORY_DESCRIPTOR *MemoryMap = NULL;
UINTN MemoryMapSize = 0;
UINTN MapKey;
UINTN DescriptorSize;
UINT32 DescriptorVersion;

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

EFI_STATUS read_elf_header(){
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

    #if DEBUG
        Print(L"Debug information about the ELF header\n");
        Print(L"Entry: %lx\n", KernelHeader.e_entry);
        Print(L"Program Header Offset: %lx\n", KernelHeader.e_phoff);
        Print(L"Program Header Count: %d\n", KernelHeader.e_phnum);
        Print(L"Program Header Size: %d\n", KernelHeader.e_phentsize);
    #endif

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

EFI_STATUS read_program_headers(){
    
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

    #if DEBUG
        for(UINTN i = 0; i < KernelHeader.e_phnum;i++){
            Print(L"\nProgram Header %d\n", i);
            Print(L"Type      : %x\n", ProgramHeaders[i].p_type);
            Print(L"Offset    : %lx\n", ProgramHeaders[i].p_offset);
            Print(L"VAddr     : %lx\n", ProgramHeaders[i].p_vaddr);
            Print(L"File Size : %lx\n", ProgramHeaders[i].p_filesz);
            Print(L"Mem Size  : %lx\n", ProgramHeaders[i].p_memsz);
            Print(L"Flags     : %x\n", ProgramHeaders[i].p_flags);
        }
    #endif

    Print(L"Kernel program header sections successfully loaded, no issues reported\n");
    return EFI_SUCCESS;

}

EFI_STATUS load_program_segments(){

    //Enumerate all the program header segments we have stored
    for(UINTN i = 0;i < KernelHeader.e_phnum;i++){
        Elf64_Phdr *seg = &ProgramHeaders[i];
        
        //Continue if the page type is not PT_LOAD
        if(seg->p_type != PT_LOAD) continue;

        //Calculate the number of pages needed for the current segment
        UINTN Pages = (seg->p_memsz + EFI_PAGE_SIZE - 1) / EFI_PAGE_SIZE;


        //Create the address pointing to where we want to load this segment
        EFI_PHYSICAL_ADDRESS Address = seg->p_paddr;

        //Now allocate the memory starting from where we need with the number of pages we need
        Status = uefi_call_wrapper(
            BS->AllocatePages,
            4,
            AllocateAddress,
            EfiLoaderData,
            Pages,
            &Address
        );

        if(EFI_ERROR(Status)){
            Print(L"Error Allocating memory pages for program section %d, EXITING\n", i);
            return Status;
        }

        //Now seek to the kernel file to read the actual contents
        Status = uefi_call_wrapper(
            KernelFile->SetPosition,
            2,
            KernelFile,
            seg->p_offset
        );

        if(EFI_ERROR(Status)){
            Print(L"Error seeking the kernel file to read program section %d, EXITING\n", i);
            return Status;
        }

        //Get the size of the data to read from the program seg, we don't care about memsize 
        //File size is the size of the data we need to read from the file
        UINTN Size = seg->p_filesz;

        Status = uefi_call_wrapper(
            KernelFile->Read,
            3,
            KernelFile,
            &Size,
            (VOID *)(UINTN) Address
        );

        if(EFI_ERROR(Status)){
            Print(L"Error reading the program section %d from the kernel ELF, EXITING\n", i);
            return Status;
        }

        if (Size != seg->p_filesz) {
            Print(L"Incomplete segment read\n");
            return EFI_LOAD_ERROR;
        }

        //Handle the cases in which memsize > filesize, needed when there are some global vars
        //Like char data[4096]
        if(seg->p_memsz > seg->p_filesz){
            VOID *Destination = (VOID *)(UINTN)(Address + seg->p_filesz);
            UINTN FillSize = seg->p_memsz - seg->p_filesz;
            uefi_call_wrapper(
                BS->SetMem,
                3,
                Destination,
                FillSize,
                0
            );
            
        }
        
        
    }

    Print(L"Kernel is successfully loaded into memory, no issues reported\n");

    return EFI_SUCCESS;
}

EFI_STATUS initialize_boot_info(BootInfo *Boot){
    EFI_GRAPHICS_OUTPUT_PROTOCOL * Gop;

    //Locate the GOP, same as what we did to locate the device from this file was executed
    Status = uefi_call_wrapper(
        BS->LocateProtocol,
        3,
        &GraphicsOutputProtocol,
        NULL,
        (VOID **)&Gop
    );

    if (EFI_ERROR(Status)) {
        Print(L"Failed to locate GOP, EXITING\n");
        return Status;
    }

    Boot->FramebufferBase =
    (VOID *)(UINTN)Gop->Mode->FrameBufferBase;

    Boot->FramebufferSize =
        Gop->Mode->FrameBufferSize;

    Boot->Width =
        Gop->Mode->Info->HorizontalResolution;

    Boot->Height =
        Gop->Mode->Info->VerticalResolution;

    Boot->PixelsPerScanLine =
        Gop->Mode->Info->PixelsPerScanLine;

    return EFI_SUCCESS;
}

EFI_STATUS get_memory_map(){
    Status = uefi_call_wrapper(
        BS->GetMemoryMap,
        5,
        &MemoryMapSize,
        MemoryMap,
        &MapKey,
        &DescriptorSize,
        &DescriptorVersion
    );

    MemoryMapSize += 2 * DescriptorSize;

    Status = uefi_call_wrapper(
        BS->AllocatePool,
        3,
        EfiLoaderData,
        MemoryMapSize,
        (VOID **)&MemoryMap
    );

    if (EFI_ERROR(Status))
        return Status;
    

    Status = uefi_call_wrapper(
        BS->GetMemoryMap,
        5,
        &MemoryMapSize,
        MemoryMap,
        &MapKey,
        &DescriptorSize,
        &DescriptorVersion
    );

    if (EFI_ERROR(Status))
        return Status;
    
    return EFI_SUCCESS;
}

EFI_STATUS jump_to_kernel(EFI_HANDLE ImageHandle) {
    KernelEntry Entry = (KernelEntry)(UINTN)KernelHeader.e_entry;
    Status = uefi_call_wrapper(
        BS->ExitBootServices,
        2,
        ImageHandle,
        MapKey
    );

    if (EFI_ERROR(Status)){
        //No prints here since boot service might be gone
        return Status;
    }

    Entry(&Boot);
    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable){
    
    InitializeLib(ImageHandle, SystemTable);
    
    //Load the kernel into a file handle
    Status = load_kernel(ImageHandle);
    if(EFI_ERROR(Status)) return Status;
    
    //Read the file handle to check if kernel is a valid 
    Status = read_elf_header();
    if(EFI_ERROR(Status)) return Status;

    //Read and store the program header sections 
    Status = read_program_headers();
    if(EFI_ERROR(Status)) return Status;

    //Now load kernel program segments into the respective pages in memory
    Status = load_program_segments();
    if(EFI_ERROR(Status)) return Status;
    
    //Initialize boot info, here we get the GOP information passed to kernel
    Status = initialize_boot_info(&Boot);
    if(EFI_ERROR(Status)) return Status;

    Status = get_memory_map();
    if (EFI_ERROR(Status)) return Status;

    //now jump to kernel
    Status = jump_to_kernel(ImageHandle);
    if(EFI_ERROR(Status)) return Status;
    
    return EFI_SUCCESS;
}