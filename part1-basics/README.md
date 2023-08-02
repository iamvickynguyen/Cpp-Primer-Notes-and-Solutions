# Part I: The Basics

## Chapter 2: Variables and Basic Types

- Avoid undefined and implementation-defined behaviour:
  - Undefined behaviour can appear to execute correctly on some compilers, but not others, and it may not work correctly in the next run on the same compiler.
  - Avoid implementation-defined because the code is nonportable. For example, assuming `int` is a fixed size.
- Be careful with expression with unsigned type
- Don't mix signed and unsigned type

```c
unsigned int u = 10;
int i = -42;
std::cout << i + i << std::endl; // -84
std::cout << u + i << std::endl; // if 32-bit int, prints 4294967264
```

```c
// infinite loop
for (unsigned int u = 10; u >= 0; --u)
    std::cout << u << std::endl;
```

- Literals:
  - Begin with 0 is octal, 0x or 0X is hex (i.e., 20 = 024 = 0x14)
  - Char and char string with prefix: `u`, `U`, `L`, `u8` (i.e., `u8"hi"`, `L'a'`)
  - Int with suffix: `u` or `U`, `l` or `L`, `ll` or `LL`, `f` or `F`, `l` or `L` (i.e., `1E-3F`, `3.14159L`, `42ULL`)
