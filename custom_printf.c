#include "custom_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int printChar(char c)
{
    return write(1, &c, 1);
}

int printString(char *str)
{
    int count = 0;

    if (str == NULL)
        str = "(null)";

    while (str[count] != '\0')
        count++;

    write(1, str, count);
    return count;
}

int printNumber(int num)
{
    char buffer[12];
    int i = 0;
    int count = 0;
    long n = num;

    if (n == 0)
        return printChar('0');

    if (n < 0)
    {
        count += printChar('-');
        n = -n;
    }

    while (n > 0)
    {
        buffer[i] = (n % 10) + '0';
        n /= 10;
        i++;
    }

    while (i > 0)
    {
        i--;
        count += printChar(buffer[i]);
    }

    return count;
}

int printBinary(unsigned int num)
{}

int handleSpecifier(char specifier, va_list args)
{
    if (specifier == 'c')
        return printChar((char)va_arg(args, int));

    if (specifier == 's')
        return printString(va_arg(args, char *));

    if (specifier == 'd' || specifier == 'i')
        return printNumber(va_arg(args, int));

    if (specifier == 'b')
        return printBinary(va_arg(args, unsigned int));

    if (specifier == '%')
        return printChar('%');

    return 0;
}

int customPrintf(const char *formatString, ...)
{
}