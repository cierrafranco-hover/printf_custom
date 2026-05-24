#include "custom_printf.h"
<<<<<<< HEAD
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
=======
#include <unistd.h>
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
{}

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
{}
>>>>>>> f2b7bdb4493fc8ec6979048b1ab1edbb4929596d
