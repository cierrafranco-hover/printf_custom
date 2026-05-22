#include "custom_printf.h"
#include <stdarg.h>
#include <unistd.h>

/* -----------------------------
   Helper: print a single char
------------------------------*/
static int printChar(char c)
{
    write(1, &c, 1);
    return 1;
}

/* -----------------------------
   Helper: print a string
------------------------------*/
static int printString(char *str)
{
    int count = 0;

    if (!str)
        return write(1, "(null)", 6);

    while (*str)
        count += write(1, str++, 1);

    return count;
}

/* -----------------------------
   Helper: print binary (%b)
------------------------------*/
static int printBinary(unsigned int n)
{
    int count = 0;
    int bits[32];
    int i = 0;

    if (n == 0)
        return write(1, "0", 1);

    while (n > 0)
    {
        bits[i++] = n % 2;
        n /= 2;
    }

    while (i--)
    {
        char c = bits[i] + '0';
        count += write(1, &c, 1);
    }

    return count;
}

/* -----------------------------
   MAIN FUNCTION
------------------------------*/
int customPrintf(char *format, ...)
{
    va_list args;
    int i = 0;
    int count = 0;

    if (!format)
        return write(1, "Error: formatString is NULL", 28);

    va_start(args, format);

    while (format[i])
    {
        if (format[i] != '%')
        {
            count += write(1, &format[i], 1);
        }
        else
        {
            i++;

            /* FIX: prevent reading past end of string */
            if (format[i] == '\0')
                break;

            if (format[i] == 'c')
                count += printChar(va_arg(args, int));

            else if (format[i] == 's')
                count += printString(va_arg(args, char *));

            else if (format[i] == 'b')
                count += printBinary(va_arg(args, unsigned int));

            else if (format[i] == '%')
                count += write(1, "%", 1);

            /* TODO: add d / i handling */
        }

        i++;
    }

    va_end(args);
    return count;
}