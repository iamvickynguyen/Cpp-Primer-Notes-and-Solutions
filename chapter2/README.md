# Chapter 2: Variables and Basic Types

## 2.1. Primitive Built-in Types

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

## 2.2. Variables

- Avoid uninitialized variables because they are hard to debug and what happens to them is undefined.
- Declaration: makes a name known to the program
- Definition: creates the associated entity, also allocates storage and may provide the variable with an initial value
- Declare but not define, use `extern` and may not provide an explicit initializer

Example:

```c
extern int i; // declares but does not define i
int j; // declares and defines j
```

- `extern` that has an initializer is a definition (i.e., `extern double pi = 3.14; // definition`)

## 2.3. Compound Types

- Compound type is a type that is defined in terms of another type
- Reference here means lvalue reference (section 13.6.1)
- A reference type refers to another type, of the form `&d`, where `d` is the name being declared

Example:

```c
int ival = 1024;
int &refVal = ival; // refVal refers to (is another name for) ival
int &refVal2; // error, a reference must be initialized
refVal = 2; // assign 2 to ival
int ii = refVal; // same as ii = ival
```

- A reference is not an object, just another name for an exisiting object

Example:

```c
int &refVal = 10; // error: initializer must be an object
```

- Pointer is a compound type that "point to" another type
- Pointer is an object, which is different from reference
- When a pointer points to an object, use deference operator (i.e., `*`) to access that object

Example

```c
int ival = 42;
int *p = &ival; // p holds the address of ival; p is a pointer to ival
cout << *p; // * yields the object to which p points; prints 42
```

- Note: some symbols have many meanings

Example:

```c
int i = 42;
int &r = i; // r is a reference
int *p;
p = &i; // & is the address-of operator
*p = i; // * is the deference operator
int &r2 = *p; // & is part of the declaration, * is the deference operator
```

- `void*`is a special pointer that can hold address of any object

## Exercises

### Exercise 2.15

Which of the following definitions, if any, are invalid? Why?

- a) int ival = 1.01;
- b) int &rval1 = 1.01;
- c) int &rval2 = ival;
- d) int &rval3;

```
a) valid
b) invalid because initializer is not an object
c) valid
d) invalid because a reference must be initialized
```

### Exercise 2.16

Which, if any, of the following assignments are invalid? If they are valid, explain what they do.

int i = 0, &r1 = i; double d = 0, &r2 = d;

- a) r2 = 3.14159;
- b) r2 = r1;
- c) i = r2;
- d) r1 = d;

```
a) valid
b) valid, automatic conversion
c) valid, value will be truncated
d) valid, value will be truncated
```

### Exercise 2.17

What does the following code print?

```
int i, &ri = i;
i = 5; ri = 10;
std::cout << i << " " << ri << std::endl;
```

```
10 10
```

### Exercise 2.18

Write code to change the value of a pointer. Write code to
change the value to which the pointer points.

```c
#include <iostream>

int main() {
  int i = 1;
  int *p = &i;
  *p = 2;
  std::cout << i << '\n';
  return 0;
}
```

### Exercise 2.21

Explain each of the following definitions. Indicate whether any are illegal and, if so, why.

int i = 0;

a) double* dp = &i;

b) int *ip = i;

c) int *p = &i;

```
a) illegal, cannot convert int* to double*
b) illegal, cannot convert int to int*
c) legal
```
