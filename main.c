#include "custom_printf.h"
#include <unistd.h>

int main(void)
{
    customPrintf("Character: %c", 'A');
    write(1, "\n", 1);

    customPrintf("String: %s", "Hello, World!");
    write(1, "\n", 1);

    customPrintf("Integer: %d", 42);
    write(1, "\n", 1);

    customPrintf("Integer with i: %i", 100);
    write(1, "\n", 1);

    customPrintf("Binary: %b", 5);
    write(1, "\n", 1);

    customPrintf("Percent sign: %%");
    write(1, "\n", 1);

    customPrintf("Nonspecifier");
    write(1, "\n", 1);

    customPrintf(NULL);
    write(1, "\n", 1);

    return 0;
}