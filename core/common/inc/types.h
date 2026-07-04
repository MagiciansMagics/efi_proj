#ifndef _TYPES_H_
#define _TYPES_H_

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

#define local static
#define flocal inline local

#define NORETURN __attribute__((noreturn))
#define PACKED __attribute__((packed))

typedef enum
{
    SUCCESS = 0,
    ERROR_INVALID_SYSTEM_TABLE,
} flags_t;

#endif