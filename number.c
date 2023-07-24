#include "main.h"

// Helper function for printing unsigned integers
static char *convert_unsigned(unsigned long num, int base, int flags, params_t *params)
{
    static char buffer[50];
    char *ptr;
    const char *array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";

    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = array[num % base];
        num /= base;
    } while (num != 0);

    return ptr;
}

// Helper function for printing signed integers
static char *convert_signed(long num, int base, int flags, params_t *params)
{
    if (num < 0) {
        params->negative = 1;
        return convert_unsigned(-num, base, flags, params);
    } else {
        return convert_unsigned(num, base, flags, params);
    }
}

// Function for printing unsigned integer numbers
int print_unsigned(va_list ap, params_t *params)
{
    unsigned long l;

    if (params->l_modifier)
        l = va_arg(ap, unsigned long);
    else if (params->h_modifier)
        l = (unsigned short int)va_arg(ap, unsigned int);
    else
        l = va_arg(ap, unsigned int);

    params->unsign = 1;
    return print_number(convert_unsigned(l, 10, CONVERT_UNSIGNED, params), params);
}

// Function for printing signed integer numbers
int print_signed(va_list ap, params_t *params)
{
    long l;

    if (params->l_modifier)
        l = va_arg(ap, long);
    else if (params->h_modifier)
        l = (short int)va_arg(ap, int);
    else
        l = va_arg(ap, int);

    return print_number(convert_signed(l, 10, 0, params), params);
}

// Function for printing addresses
int print_address(va_list ap, params_t *params)
{
    unsigned long int n = va_arg(ap, unsigned long int);

    if (!n)
        return _puts("(nil)");

    char *str = convert_unsigned(n, 16, CONVERT_UNSIGNED | CONVERT_LOWERCASE, params);
    *--str = 'x';
    *--str = '0';
    return print_number(str, params);
}
