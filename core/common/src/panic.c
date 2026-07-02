#include <panic.h>

NORETURN
void
panic(void)
{
    for (;;)
    {
        asm volatile ("hlt");
    }
}