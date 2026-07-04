#include <gfx/print.h>
#include <global.h>

flocal
char*
convert(unsigned int num, int base)
{
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50];
    char* ptr;

    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = Representation[num % base];
        num /= base;
    } while (num != 0);

    return ptr;
}

flocal
void
output_ascii(EFI_SYSTEM_TABLE *st, const char *str)
{
    uint16_t buffer[128];
    uint64_t i = 0;

    while (str[i] && i < 127)
    {
        buffer[i] = (uint16_t)str[i];
        i++;
    }

    buffer[i] = L'\0';

    st->ConOut->OutputString(st->ConOut, buffer);
}

void
print(const char *format, ...)
{
    EFI_SYSTEM_TABLE *sys_table = get_system_table();

    va_list arg;
    va_start(arg, format);

    const char *traverse = format;

    while (*traverse)
    {
        if (*traverse != '%')
        {
            uint16_t ch[2] = {(uint16_t)*traverse, 0};
            sys_table->ConOut->OutputString(sys_table->ConOut, ch);
            traverse++;
            continue;
        }

        traverse++;

        if (*traverse == '\0')
            break;

        switch (*traverse)
        {

            case 'c':
            {
                uint16_t ch[2] = {(uint16_t)va_arg(arg, int), 0};
                sys_table->ConOut->OutputString(sys_table->ConOut, ch);
                break;
            }

            case 's':
            {
                char* s = va_arg(arg, char*);
                output_ascii(sys_table, s);
                break;
            }

            case 'd':
            {
                int i = va_arg(arg, int);
                if (0 > i)
                {
                    i = -i;
                    sys_table->ConOut->OutputString(sys_table->ConOut, L"-");
                }
                output_ascii(sys_table, convert(i, 10));
                break;
            }

            case 'x':
            {
                output_ascii(sys_table, convert(va_arg(arg, unsigned int), 16));
                break;
            }

            case '%':
            {
                uint16_t ch[2] = {L'%', 0};
                sys_table->ConOut->OutputString(sys_table->ConOut, ch);
                break;
            }

            default:
                break;
        }

        traverse++;
    }

    va_end(arg);
}