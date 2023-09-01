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

- `int* p1, p2; // p1 is a pointer to int; p2 is an int`

- Writing `int* p;` is somewhat misleading because the base type of variable `p` is `int`, not `int*`. `*` modifies the type of `p`

- There is no limits to the number of type modifiers (i.e., `*`, `**`, `***`, etc.)

Example:

```c
int ival = 1024;
int *pi = &ival; // pi points to an int
int **ppi = &pi; // ppi points to a pointer to an int
```

```c
// Deferencing pointers
cout << "The value of ival\n"
    << "direct value: " << ival << "\n"
    << "indirect value: " << *pi << "\n" 
    << "doubly indirect value: " << **ppi << endl;
```

- We can have a reference to a pointer because a pointer is an object

Example:

```c
int i = 42;
int *p; // p is a pointer to int
int *&r = p; // r is a reference to the pointer p
r = &i; // r refers to a pointer; assigning &i to r makes p point to i
*r = 0; // dereferencing r yields i, the object to which p points; changes i to 0
```

- To understand complicated pointer or reference declarations, read them from right to left

## 2.4 `const` Qualifier

- `const` object must be initialized because we can't change the value of a `const`
- By default, `const` objects are loval to a file
- Use `extern` to share a `const` object among multiple files

Example:

```c
// file_1.cc defines and initializes a const that is accessible to other files extern const int bufSize = fcn();
// file_1.h
extern const int bufSize; // same bufSize as defined in file_1.cc
```

#### 2.4.1. References to `const`

- `const` reference means reference to `const`. There is no such thing is `const` reference as a reference is not an object, we cannot make a reference itself `const`

Examples:

```c
const int ci = 1024;
const int &r1 = ci; // ok: both reference and underlying object are const
r1 = 42; // error: r1 is a reference to const
int &r2 = ci; // error: non const reference to a const object
```

```c
int i = 42;
const int &r1 = i; // we can bind a const int& to a plain int object
const int &r2 = 42; // ok: r1 is a reference to const
const int &r3 = r1 * 2; // ok: r3 is a reference to const
int &r4 = r * 2; // error: r4 is a plain, non const reference
```

- A reference to `const` may refer to an object that is NOT `const`. Thus, binding a reference to `const` to an object says nothing about whether the object is `const` or not.

Example:

```c
int i = 42;
int &r1 = i; // r1 bound to i
const int &r2 = i; // r2 also bound to i; but cannot be used to change i
r1 = 0; // r1 is not const; i is now 0
r2 = 0; // error: r2 is a reference to const
```

#### 2.4.2 Pointers and `const`

- A pointer to `const` may not be used to change the object

Example:

```c
const double pi = 3.14; // pi is const; its value may not be changed
double *ptr = &pi; // error: ptr is a plain pointer
const double *cptr = &pi; // ok: cptr may point to a double that is const
*cptr = 42; // error: cannot assign to *cptr
```

- A pointer to `const` can points to a `nonconst` object

Example:

```c
double dval = 3.14; // dval is a double; its value can be changed
const double *cptr = &dval; // ok, but can't change dval through cptr
```

- A `const` pointer must be initialized, and its value (i.e., the address that it holds) may not be changed.
- A pointer to `const` is indicated by putting the `const` after `*`. This means it is a pointer, not a pointed-to-type that is `const`.

Example:

```c
int errNumb = 0;
int *const curErr = &errNumb; // curErr will always point to errNumb
const double pi = 3.14159;
const double *const pip = &pi; // pip is a const pointer to a const object
```

- In the example above, `pip` is a `const` pointer to `const`, so neither the value of the object (i.e., `pi`) nor the addresses stored in `pip` can be changed. However, `curErr` addresses a plain, `nonconst` int, so `curErr` can be used to change the value of `errNumb`.

Example:

```c
*pip = 2.72; // error; pip is a pointer to const
// if the object to which curErr points (i.e., errNumb) is nonzero
if (*curErr) {
 errorHandler();
 *curErr = 0; // ok: reset the value of the object to which curErr is bound
}
```

#### 2.4.3 Top-level `const`

- Top-level `const` indicates the pointer itself is a `const`
- Low-level `const` indicates the pointer can point to a `const` object

Example:

```c
int i = 0;
int *const p1 = &i; // we can't change the value of p1; const is top-level
const int ci = 42; // we cannot change ci; const is top-level
const int *p2 = &ci; // we can change p2; const is low-level
const int *const p3 = p2; // right-most const is top-level, left-most is not
const int &r = ci; // const in reference types is always low-level
```

- When copying an object, top-level `const` is ignored
 
Example:

```c
i = ci; // ok: copying the value of ci; top-level const in ci is ignored
p2 = p3; // ok: pointed-to type matches; top-level const in p3 is ignored
```

- When copying an object, low-level `const` is not ignored

Example:

```c
int *p = p3; // error: p3 has a low-level const but p doesn't
p2 = p3; // ok: p2 has the same low-level const qualification as p3
p2 = &i; // ok: we can convert int* to const int*
int &r = ci; // error: can't bind an ordinary int& to a const int object
const int &r2 = i; // ok: can bind const int& to plain int
```

#### 2.4.4 `constexpr` and Constant Expressions

- The value of a constant expression is evaluated at compile time
- `constexpr` is used to ask the compiler to verify if a variable is a constantexpression
- `constexpr` variables are implicitly `const` and must be initialized by constant expressions

Example:

```c
constexpr int mf = 20; // 20 is a constant expression
constexpr int limit = mf + 1; // mf + 1 is a constant expression
constexpr int sz = size(); // ok only if size is a constexpr function
```

- When declaring a pointer with `constexpr`, `constexpr` imposes a top-level `const`

Example:

```c
const int *p = nullptr; // p is a pointer to a const int
constexpr int *q = nullptr; // q is a const pointer to int
```

## 2.5 Dealing with Types

### 2.5.1 Type Aliases

- Traditionally, use `typedef`

Example:

```c
typedef double wages; // wages is a synonym for double
typedef wages base, *p; // base is a synonym for double, p for double*
```

- The new way, use alias declaration (i.e., `using` and `=`)

Example:

```c
using SI = Sales_item; // SI is a synonym for Sales_item
```

- Using type aliases with compound types and `const` can yield surprising results

Example:

```c
typedef char *pstring;
const pstring cstr = 0; // cstr is a constant pointer to char
const pstring *ps; // ps is a pointer to a constant pointer to char
```

- Conceptually replacing the alias with its type can be incorrect

Example:

```c
const char *cstr = 0; // wrong interpretation of const pstring cstr
```

### 2.5.2 The `auto` Type Specifier

- Let the compiler figure out the type of an expression for us by using `auto`

Example:

```c
auto i = 0, *p = &i; // ok: i is int and p is a pointer to int
auto sz = 0, pi = 3.14; // error: inconsistent types for sz and pi
```

- `auto` ignores top-level `const`

Example:

```c
int i = 0;
const int ci = i, &cr = ci;
auto b = ci; // b is an int (top-level const in ci is dropped)
auto c = cr; // c is an int (cr is an alias for ci whose const is top-level)
auto d = &i; // d is an int*(& of an int object is int*)
auto e = &ci; // e is const int*(& of a const object is low-level const)
```

- Remember a reference or pointer is part of a declarator, not the base type

Example:

```c
auto k = ci, &l = i; // k is int; l is int&
auto &m = ci, *p = &ci; // m is a const int&;p is a pointer to const int
auto &n = i, *p2 = &ci; // error: type deduced from i is int; type deduced from &ci is const int
```

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

### Exercise 2.24

Why is the initialization of p legal but that of lp illegal?

int i = 42; void \*p = &i; long \*lp = &i;

```
void* is a special pointer that can point to any data type
```

### Exercise 2.25

Determine the types and values of each of the following variables.

a) int* ip, i, &r = i;

b) int i, \*ip = 0;

c) int* ip, ip2;

```
a) ip, r, i: base type int, ip is a pointer to int, i is an int, r is a reference to i
b) i, ip: base type int, value of i is 0, ip is a null pointer
c) ip, ip2: base type int, ip is a pointer to int, ip2 is an int 
```

### Exercise 2.26

Which of the following are legal? For those that are illegal, explain why.

a) const int buf;

b) int cnt = 0;

c) const int sz = cnt;

d) ++cnt; ++sz;

```
a) Illegal, const object must be initialized
b) Legal
c) Legal
d) ++cnt is legal, ++sz is illegal because const object cannot be modified
```

### Exercise 2.27

 Which of the following initializations are legal? Explain why.

a) int i = -1, \&r = 0;

b) int \*const p2 = \&i2;

c) const int i = -1, \&r = 0;

d) const int \*const p3 = \&i2;

e) const int \*p1 = \&i2;

f) const int \&const r2;

g) const int i2 = i, \&r = i;

```c
a) illegal, r must refer to an object
b) legal
c) legal, r is a reference to const
d) legal
e) legal
f) illegal, r2 is reference that cannot be const
g) legal
```

### Exercise 2.28

Explain the following definitions. Identify any that are illegal.

a) int i, \*const cp;

b) int \*p1, \*const p2;

c) const int ic, \&r = ic;

d) const int \*const p3;

e) const int \*p;

```c
a) illegal, cp is a const pointer and it must be initialized
b) illegal, p2 is a const pointer and it must be initialized
c) illegal, ic must be initialized
d) illegal, p3 is a const pointer and it must be initialized
e) legal, p is a pointer to const int
```

### Exercise 2.29

Using the variables in the previous exercise, which of the following assignments are legal? Explain why.

a) i = ic;

b) p1 = p3;

c) p1 = \&ic;

d) p3 = \&ic;

e) p2 = p1;

f) ic = \*p3;

```c
a) legal
b) illegal, p1 is a plain pointer so it cannot point to a const pointer
c) illegal, ic is a const int
d) illegal, p3 is a const pointer
e) illegal, p2 is a const pointer
f) illegal, ic is a const int
```

### Exercise 2.30

For each of the following declarations indicate whether the object being declared has top-level or low-level const.

```c
const int v2 = 0; int v1 = v2;
int *p1 = &v1, &r1 = v1;
const int *p2 = &v2, *const p3 = &i, &r2 = v2; 
```

```c
v2 has top-level const
p2 has low-level const
p3 has both low-level and top-level consts
r2 has low-level const
```

### Exercise 2.31

Given the declarations in the previous exercise determine whether the following assignments are legal. Explain how the top-level or low-level const applies in each case.

```c
r1 = v2; // Ok: top-level const can be ignored
p1 = p2; // Error: p2 has low-level const but p1 doesn't
p2 = p1; // Ok: can convert int* to const int*
p1 = p3; // Error: p3 has low-level const but p1 doesn't
p2 = p3; // Ok: top-level const can be ignored, p2 has p3 have the same low-level const
```

### Exercise 2.32

Is the following code legal or not? If not, how might you make it legal?

int null = 0, \*p = null;

```c
Illegal
Fix: int null = 0; *p = nullptr; // or int *p = 0;
```

### Exercise 2.33

Using the variable definitions from this section, determine what happens in each of these assignments:

```c
a = 42; // Ok
b = 42; // Ok
c = 42; // Ok
d = 42; // Error, d is int*, fix: *d = 42;
e = 42; // Error, e is const int*, fix: e = &c
g = 42; // Error, g is const int& that is bound to ci
```

### Exercise 2.35

Determine the types deduced in each of the following definitions. Once you’ve figured out the types, write a program to see whether you were correct.

const int i = 42;

auto j = i; const auto \&k = i; auto \*p = \&i;

const auto j2 = i, \&k2 = i;

```c
j is int
k is const int&
p is const int*
j2 is const int
k2 is const int&
```
