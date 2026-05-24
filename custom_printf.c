#include "custom_printf.h"#include <unistd.h>
#include <stdarg.h>

static int printChar(char c)
{
    return (int)write(1, &c, 1);
}

static int printString(char *str)
{
    if (str == NULL)
        str = "(null)";
    int len = 0;
    while (str[len])
        len++;
    return (int)write(1, str, len);
}

static int printNumber(int num)
{
    char buffer[12];
    int i = 0;
    int count = 0;
    unsigned int u;

    if (num == 0)
        return printChar('0');
    if (num < 0)
    {
        count += printChar('-');
        u = (unsigned int)(-(num + 1)) + 1;
    }
    else
    {
        u = (unsigned int)num;
    }
    while (u > 0)
    {
        buffer[i] = (u % 10) + '0';
        u /= 10;
        i++;
    }
    while (i > 0)
    {
        i--;
        count += printChar(buffer[i]);
    }
    return count;
}

static int printBinary(unsigned int num)
{ int count = 0;

    //If number is greater than 1, keep dividing recursively 
    if (num > 1)
    {
        count += printBinary(num / 2);
    }

    // Print current binary digit 
    count += printChar((num % 2) + '0');

    return count;}

static int handleSpecifier(char specifier, va_list *args)
{
    if (specifier == 'c')
        return printChar((char)va_arg(*args, int));
    if (specifier == 's')
        return printString(va_arg(*args, char *));
    if (specifier == 'd' || specifier == 'i')
        return printNumber(va_arg(*args, int));
    if (specifier == 'b')
        return printBinary(va_arg(*args, unsigned int));
    if (specifier == '%')
        return printChar('%');
    return 0;
}

int customPrintf(const char *formatString, ...)
{ va_list args;
    int i = 0;
    int count = 0;

    va_start(args, formatString);

    while (formatString[i] != '\0')
    {
        if (formatString[i] == '%')
        {
            i++;

            /* Handle format specifier */
            count += handleSpecifier(formatString[i], &args);
        }
        else
        {
            /* Print regular character */
            count += printChar(formatString[i]);
        }

        i++;
    }

    va_end(args);

    return count;}