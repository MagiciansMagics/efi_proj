section .text

[GLOBAL efi_main]
[EXTERN main]

efi_main:

    ; RCX = ImageHandle
    ; RDX = SystemTable
    ;
    ; Microsoft x64 ABI:
    ;   RCX = 1st argument
    ;   RDX = 2nd argument
    ;   R8  = 3rd argument
    ;   R9  = 4th argument

    jmp main