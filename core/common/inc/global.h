#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#pragma once

#include <efi.h>

// Purpose for the global is so that variables can be accessed from anywhere,
// without it needing to be transferred via function parameter

EFI_SYSTEM_TABLE*
get_system_table(void);

void
set_system_table(EFI_SYSTEM_TABLE* SystemTable);

#endif