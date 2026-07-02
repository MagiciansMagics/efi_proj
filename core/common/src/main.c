#include <main.h>
#include <efi/efi.h>
#include <panic.h>

void
main(unsigned long image_handle, EFI_SYSTEM_TABLE* SystemTable)
{
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Magic?");
    panic();
}