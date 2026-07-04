#ifndef _EFI_H_
#define _EFI_H_

#pragma once

#include <types.h>

#define L (uint16_t*)
#define EFIAPI __attribute__((ms_abi))
#define IN
#define OUT

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
typedef void* EFI_HANDLE;
typedef uint64_t EFI_STATUS;
typedef uint64_t EFI_TPL;

typedef enum
{
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum
{
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIoPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiUnacceptedMemoryType,
    EfiMaxMemoryType,
    MEMORY_TYPE_OEM_RESERVED_MIN = 0x70000000,
    MEMORY_TYPE_OEM_RESERVED_MAX = 0x7FFFFFFF,
    MEMORY_TYPE_OS_RESERVED_MIN  = 0x80000000,
    MEMORY_TYPE_OS_RESERVED_MAX  = 0xFFFFFFFF,
} EFI_MEMORY_TYPE;

typedef EFI_STATUS (EFIAPI* EFI_TEXT_RESET)
(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
    IN bool ExtendedVerification
);

typedef EFI_STATUS (EFIAPI* EFI_TEXT_STRING)
(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
    IN uint16_t* str
);

typedef EFI_TPL (EFIAPI* EFI_RAISE_TPL)
(
    IN EFI_TPL NewTpl
);

typedef EFI_TPL (EFIAPI* EFI_RESTORE_TPL)
(
    IN EFI_TPL OldTpl
);

typedef EFI_STATUS (EFIAPI* EFI_ALLOCATE_PAGES)
(
    IN EFI_ALLOCATE_TYPE Type,
    IN EFI_MEMORY_TYPE MemoryType,
    IN uint64_t Pages,
    IN OUT uint64_t* Memory
);

typedef EFI_STATUS (EFIAPI* EFI_FREE_PAGES)
(
    IN uint64_t Memory,
    IN uint64_t Pages
);

typedef struct
{
    uint32_t Type;
    uint64_t PhysicalStart;
    uint64_t VirtualStart;
    uint64_t NumberOfPages;
    uint64_t Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef EFI_STATUS (EFIAPI* EFI_GET_MEMORY_MAP)
(
    IN OUT uint64_t* MemoryMapSize,
    OUT EFI_MEMORY_DESCRIPTOR* MemoryMap,
    OUT uint64_t* MapKey,
    OUT uint64_t* DescriptorSize,
    OUT uint32_t* DescriptorVersion
);

typedef EFI_STATUS (EFIAPI* EFI_ALLOCATE_POOL)
(
    IN EFI_MEMORY_TYPE PoolType,
    IN uint64_t Size,
    OUT void** Buffer
);

typedef EFI_STATUS (EFIAPI* EFI_FREE_POOL)
(
    IN void* Buffer
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

    EFI_RAISE_TPL RaiseTPL;

    EFI_RESTORE_TPL RestoreTPL;

    EFI_ALLOCATE_PAGES AllocatePages;

    EFI_FREE_PAGES FreePages;

    EFI_GET_MEMORY_MAP GetMemoryMap;

    EFI_ALLOCATE_POOL AllocatePool;

    EFI_FREE_POOL FreePool;
} EFI_BOOT_SERVICES;

typedef struct
{
    EFI_TABLE_HEADER hdr;

    uint16_t* FirmwareVendor;

    uint32_t FirmwareRevision;

    EFI_HANDLE ConsoleInHandle;

    void* ConIn;

    EFI_HANDLE ConsoleOutHandle;

    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;

    EFI_HANDLE StandardErrorHandle;

    void* RuntimeServices;

    EFI_BOOT_SERVICES* BootServices;
} EFI_SYSTEM_TABLE;

#endif