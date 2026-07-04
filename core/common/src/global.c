#include <global.h>

EFI_SYSTEM_TABLE* g_systemtable = NULL;

EFI_SYSTEM_TABLE*
get_system_table(void)
{
    return g_systemtable;
}

void
set_system_table(EFI_SYSTEM_TABLE* SystemTable)
{
    if (g_systemtable)
        return;

    g_systemtable = SystemTable;
}