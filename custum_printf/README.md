# printf_custom

A custom implementation of the C standard `printf` function, built from scratch using only low-level system calls.

---

## Group Members

- **JT**
- **Cierra**

---

## Description

`custom_printf` is a C project that replicates core functionality of the standard `printf` function without using it. Output is written directly to standard output using the `write` system call. The project supports several format specifiers and handles edge cases such as null strings, `INT_Min`, and trailing `%` characters.

---

## Supported Format Specifiers

| Specifier | Description
|-----------|-------------------------------------|
| `%c`      |Print a single character             |
| `%s`      | Print a string (`NULL` -> `(null)`) |
| `%d`      | Print a signed decimal integar      |  
| `%i`      | Print a signed integer              |
| `%b`      | Print an unsigned integer in binary |
| `%%`      | Print a literal `%` character       |

---

## Project Structure

printf_custom/
|-- custom_printf.h # Header file - declares cusromPrintf
|-- custom_printf.c # Core implementation - logic is here
|__ main.c          # Entry point - test cases for all  specifiers

---

### File Breakdown

**`custom_printf.h`**
- Include gaurd (`#ifndef / #define / #endif`)
- Single public declaration: `int customPrintf(const char *formatString, ...)`
- Include `<stdarg.h>` for variadic argument support

**`custom_print.c`**
- All helper functions are marked `static` (internal linkage only)
- `printChar(char c)` — writes one character via `write(1, ...)`
- `printString(char *str)` — handles `NULL` input, computes length manually, writes via `write`
- `printNumber(int num)` — handles `0`, negatives, and `INT_MIN` safely using `unsigned int` internally
- `printBinary(unsigned int num)` — recursive implementation; handles `0` edge case
- `handleSpecifier(char specifier, va_list *args)` — dispatches to the correct print function; `va_list` passed by pointer to avoid undefined behavior
- `customPrintf(const char *formatString, ...)` — main function; walks the format string, handles `NULL` input, guards against trailing `%`

**`main.c`**
- Tests each supported specifier
- Uses `write(1, "\n", 1)` for newlines to stay consistent with the no-`printf` constraint

---

## Flowchart

```
customPrintf(formatString, ...)
        │
 formatString == NULL?
   │           │
  YES          NO
   │           │
 Write      va_start(args)
 error           │
 message         |
 return    Walk format string char by char
                 │
        _________|_________
        │                 │
    char == '%'?       Regular char
        │                 │
       YES            printChar(c)
        │
  next char == '\0'?
   │           │
  YES          NO
   │           │
printChar('%') handleSpecifier(specifier, &args)
  break              │
              _______|_____________________
              │      │      │      │      │
             'c'    's'   'd'/'i' 'b'   '%%'
              │      │      │      │      │
         printChar  print  print  print  print
                   String Number Binary  '%'
                                  │
                             (recursive)
                             num > 1?
                              │    │
                             YES   NO
                              │    │
                         printBinary  printChar
                          (num/2)    (num%2+'0')
```

---

## How to Run

### Requirements
- GCC compiler
- Linux or any POSIX-compliant environment (macOS, WSL, GitHub Codespaces)

### Compile

```bash
gcc -Wall -Werror -Wextra -pedantic -o printf_test main.c custom_printf.c
```

### Run

```bash
./main
```

### Expected Output

```
Character: A
String: Hello, World!
Integer: 42
Integer with i: 100
Binary: 101
Percent sign: %
Nonspecifier
Error: formatString is NULL
```

---

## Environment

Built and run successfully on:

- **OS**: Ubuntu 22.04
- **Editor**: Visual Studio Code
- **Compiler**: GCC 11.4.0
- **Standard**: C99 / POSIX
- **Flags**: `-Wall -Werror -Wextra -pedantic`

---

## What Was Not Completed / Future Improvements

The following specifiers and features were not implemented and would be natural next steps:

| Feature                       | Notes                                                  |
|-------------------------------|--------------------------------------------------------|
| `%u`                          | Unsigned decimal integer                               |
| `%o`                          | Octal representation                                   |
| `%x` / `%X`                   | Hexadecimal (lower and upper case)                     |
| `%p`                          | Pointer address                                        |
| Width & precision flags       | e.g. `%-10s`, `%05d`, `%.2f`                           |
| `%f` / `%e`                   | Floating point support                                 |
| `%l`, `%h` length modifiers   | `long`, `short` variants                               |
| Return value of `write`       | Currently ignored; should check for partial writes     |
| Thread safety                 | No locking around `write` calls                        |

---

## Known Issues / Notes

- Passing a literal `NULL` as the format string is undefined behavior per the C standard. Our NULL guard handles it gracefully, but some compilers may warn or optimize around it.
- Unrecognized specifiers (e.g. `%q`) are silently ignored and contribute `0` to the return count.
- A trailing lone `%` at the end of a format string prints `%` and stops — matching reasonable expected behavior.