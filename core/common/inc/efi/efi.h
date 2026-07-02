#ifndef _EFI_H_
#define _EFI_H_

#pragma once

#include <types.h>

#define L (uint16_t*)

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
typedef void* EFI_HANDLE;

#if __x86_64__
    #define EFIAPI __attribute__((ms_abi))
    typedef uint64_t EFI_STATUS;
#endif
 
#if __i386__
    #define EFIAPI __attribute__((cdecl,regparm(0)))
    typedef uint32_t EFI_STATUS;
#endif

typedef EFI_STATUS (EFIAPI* EFI_TEXT_RESET)
(
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
    bool ExtendedVerification
);

typedef EFI_STATUS (EFIAPI* EFI_TEXT_STRING)
(
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
    uint16_t* str
);

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
{
    EFI_TEXT_RESET Reset;
    EFI_TEXT_STRING OutputString;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct
{
    uint64_t Signature;
    uint32_t Revision;
    uint32_t HeaderSize;
    uint32_t CRC32;
    uint32_t Reserved;
} EFI_TABLE_HEADER;

typedef struct
{
    EFI_TABLE_HEADER hdr;

    uint16_t* FirmwareVendor;

    uint32_t FirmwareRevision;

    EFI_HANDLE ConsoleInHandle;

    void* ConIn;

    EFI_HANDLE ConsoleOutHandle;

    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;
} EFI_SYSTEM_TABLE;

#endif