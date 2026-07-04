#include <main.h>
#include <global.h>
#include <gfx/print.h>
#include <panic.h>

void
main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE* SystemTable)
{
    set_system_table(SystemTable);

    // Clear the screen, mainly for emulators such as qemu that might display unnecessary text
    SystemTable->ConOut->Reset(SystemTable->ConOut, false);

    print("Welcome! Its still in progress...");

    panic();
}