# Chapter 4. Expressions

## 4.1. Fundamentals

### 4.1.1. Basic Concepts

- An expression is composed of >= 1 *operands* and yields a result when it is evaluated
- *Overloaded operators*: we give an alternative meaning to existing operators
- When we use an object as an *rvalue*, we use the object's value (its contents)
- When we use an object as an *lvalue*, we use the object's identity (its location in memory)
- We can use an *lvalue* when an *rvalue* is required, but not the other way around
- `decltype` for *lvalues* and *rvalues* are different

Example:

```
Assume p is an int*
decltype(*p) is int& ; because dereference yields an lvalue
decltype(&p) is int** ; because the address-of operator yields an rvalue,
                      ; that is, a pointer to a pointer to type int
```

### 4.1.2. Precedence and Associativity

- *Compound expression*: an expression with >= 2 operators (i.e., `3 + 4 * 5`)

### 4.1.3. Order of Evaluation

- *Precedence* specifies how the operands are grouped, but says nothing about the order in which the operands are evaluated

Example:

```c
int i = f1() * f2(); // don't know whether f1 is called before f2 or vice versa
```

- `<<` operator doesn't guarantee when and how its operands are evaluated

Example:

```c
int i = 0;
cout << i << " " << ++i << endl; // undefined
```

## 4.2. Arithmetic Operators

- Becareful with overflow and undefined results (i.e, division by 0)

## 4.3. Logical and Relational Operators

- *Short-circuit evaluation*: the right operand is evaluated iff the left operand does not determine the result (for `&&` and `||`)

## 4.4. Assignment Operators

- The left-hand operand of an assignment operator must be a modifiable *lvalue*

Examples:

```c
int i = 0, j = 0, k = 0; // initializations, not assignment
const int ci = i; // initialization, not assignment
```

```c
1024 = k; // error: literals are rvalues
i + j = k; // error: arithmetic expressions are rvalues
ci = k; // error: ci is a const (nonmodifiable) lvalue
```

```c
k = 0; // result: type int, value 0
k = 3.14159; // result: type int, value 3
```

- Assignment is right associative

Example:

```c
int ival, jval;
ival = jval = 0; // ok: each assigned 0
                 // jval = 0, then ival = jval
```

- Each object in a multiple assignment must have the same type as its right-hand neighbor or a type to which that neighbor can be converted

Example:

```c
int ival, *pval; // ival is an int; pval is a pointer to int
ival = pval = 0; // error: cannot assign the value of a pointer to an int
```

- Assignment has low precedence, so parentheses are needed

Example:

```c
int i;
while ((i = get_value()) != 42) {
    // do something ...
}
```

## 4.5. Increment and Decrement Operators

- `cout << *iter++ << endl;` is less-error-prine than the more verbose `cout << *iter << endl; ++iter;`
- Operands can be evaluated in any order

Example:

```c
// the behavior of the following loop is undefined!
while (beg != s.end() && !isspace(*beg))
    *beg = toupper(*beg++); // error: this assignment is undefined

/*
The compiler might evaluate this expression as either:
*beg = toupper(*beg); // execution if left-hand side is evaluated first
*(beg + 1) = toupper(*beg); // execution if right-hand side is evaluated
first
*/
```

## 4.6. The Member Access Operators

- Access member with dot (`.`) and arrow (`->`)
- `ptr->mem` is same as `(*ptr).mem`

## 4.7. The Conditional Operator

- `cond ? expr1 : expr2;`
- The conditional operator has fairly low precedence. Thus, need parentheses

Examples:

```c
cout << ((grade < 60) ? "fail" : "pass"); // prints pass or fail
cout << (grade < 60) ? "fail" : "pass"; // prints 1 or 0!
cout << grade < 60 ? "fail" : "pass"; // error: compares cout to 60
```

## 4.8. The Bitwise Operators

- Because there are no guarantees for how the sign bit is handled, unsigned types with the bitwise operators is recommended

## 4.9. The sizeof Operator

- The `sizeof` operator returns the size, in bytes
- `sizeof` doesn't evaluate its operand

Example:

```c
sizeof(ia)/sizeof(*ia); // returns the number of elements in ia
```

## 4.10. Comma Operator

- The comma operator guarantees the order in which its operands are evaluated

Examples:

```c
int a = 4, b = 5;
for (int i = 0, j = 5; i < 10; ++i, --j) // do something ...
```

## 4.11. Type Conversions

- Implicit conversions: conversions are carried out automatically
- Explicit conversions: force an object to be converted to a different type
- *Casts* are inherently dangerous constructs
- Named cast has the form: `cast-name<type>(expression);`. *Cast-name* can be `static_cast`, `dynamic_cast`, `const_cast`, and `reinterpret_cast`
- `static_cast`:
    - Used for any well-defined type conversion, other than low-level `const` (i.e., `double slope = static_cast<double>(j) / i;`)
    - Used to convert larger arithmetic type to a smaller one
    - Used for a conversion that the compiler won't generate automatically (i.e., `void* p = &d; double *dp = static_cast<double*>(p);`)
- `const_cast`: convert `const` object to a nonconst object
- `reinterpret_cast`:
    - Performs a low-level reinterpretation of the bit patterns of its operands (i.e., `int *ip; char *pc = reinterpret_cast<char*>(ip);`)
    - It is inherently machine dependent
- Old-style cast:
    - Same as `static_cast` or `const_cast`. If neither is legal, then it performs same as `reinterpret_cast`
    - Example: `char *pc = (char*) ip; // ip is a pointer to int`

## Exercises

### Exercise 4.3

Order of evaluation for most of the binary operators is left undefined to give the compiler opportunities for optimization. This strategy presents a trade-off between efficient code generation and potential pitfalls in the use of the language by the programmer. Do you consider that an acceptable trade-off? Why or why not?

> Yes, but programmers have to be careful. Performance in C++ is important, so compiler's features are good. However, we also don't want bugs, so it's best to avoid undefined behaviours. For example, `cout << i << ++i` should not appear in the code.

### Exercise 4.6

Write an expression to determine whether an int value is even or odd.

```c
int x = 3;
cout << ((x % 2 == 0) ? "Even" : Odd) << '\n';
```

### Exercise 4.7

What does overflow mean? Show three expressions that will overflow.

> Overflow means the value is outside the range of that the type can represent

```c
int a = INT_MAX; ++a;
short b = SHRT_MIN; --b;
char c = 300;
```

### Exercise 4.9

Explain the behavior of the condition in the following if:

```c
const char *cp = "Hello World";
if (cp && *cp)
```

> It checks if `cp` is not a nullptr and the content of `cp` is not empty. Result of the expression is true  

### Exercise 4.10

Write the condition for a while loop that would read ints from the standard input and stop when the value read is equal to 42.

```c
int x;
while (cin >> x && x != 42)
```

### Exercise 4.11

Write an expression that tests four values, a, b, c, and d, and ensures that a is greater than b, which is greater than c, which is greater than d.

```c
a> b && b > c && c > d
```

### Exercise 4.12

Assuming i, j, and k are all ints, explain what i != j < k means.

> It means `i != (j < k)`

### Exercise 4.13

What are the values of i and d after each assignment?

```c
int i; double d;
(a) d = i = 3.5; // i = 3, d = 3.0
(b) i = d = 3.5; // d = 3.5, i = 3
```

### Exercise 4.15

The following assignment is illegal. Why? How would you correct it?

```c
double dval; int ival; int *pi;
dval = ival = pi = 0;
```

> Illegal because `pi` is a pointer to int, cannot assign `int*` to `int`

```c
// Fix
dval = ival = 0;
pi = 0;
```

### Exercise 4.16

Although the following are legal, they probably do not behave as the programmer expects. Why? Rewrite the expressions as you think they should be.

```c
(a) if (p = getPtr() != 0) // this is same as p = (getPtr() != 0)
                           // fix: if ((p = getPtr()) != 0)
(b) if (i = 1024) // same as if (true)
                  // fix: if (i == 1024)
```

### Exercise 4.17

Explain the difference between prefix and postfix increment.

> Prefix: increment first, then return the incremented value. Postfix: return the original value, then increment it. Prefix is more efficient because the compiler increment the value of that object, whereas the compiler has to create a temporary object for postfix.

### Exercise 4.19

Given that ptr points to an int, that vec is a vector\<int>, and that ival is an int, explain the behavior of each of these expressions. Which, if any, are likely to be incorrect? Why? How might each be corrected?

```c
(a) ptr != 0 && *ptr++ // check if ptr isn't nullptr and check ptr value
(b) ival++ && ival // check ival and ival + 1 if equal 0 
(c) vec[ival++] <= vec[ival] // incorrect, undefined behaviour
                             // fix: vec[ival] <= vec[ival+1];
```

### Exercise 4.20

Assuming that iter is a vector\<string>::iterator, indicate which, if any, of the following expressions are legal. Explain the behavior of the legal expressions and why those that aren’t legal are in error.

```c
(a) *iter++; // legal, deference iter then increment the value
(b) (*iter)++; // illegal, *iter is string, cannot increment a string
(c) *iter.empty() // illegal, same as *(iter.empty())
(d) iter->empty(); // legal, check if value of the string is empty
(e) ++*iter; // illegal, cannot increment a string
(f) iter++->empty(); // legal, check if the current string is empty, then increment iter 
```

### Exercise 4.23

The following expression fails to compile due to operator precedence. Using Table 4.12 (p. 166), explain why it fails. How would you fix it?

```c
string s = "word";
string pl = s + s[s.size() - 1] == 's' ? "" : "s" ;
```

> Fails because of the operator precedence: `+` > `==` > `?:`. This is same as `string pl = ((s + s[s.size() - 1]) == 's') ? "" : "s";` 

### Exercise 4.25

What is the value of ~'q' << 6 on a machine with 32-bit ints and 8 bit chars, that uses Latin-1 character set in which 'q' has the bit pattern 01110001?

```c
~'q': 10001110
~'q' << 6: 11111111111111111111111110001110 which is 4294960000 in decimal
Since 4294960000 doesn't fit 32-bit int, the value is wrap around. The output is -7296
```

### Exercise 4.29

Predict the output of the following code and explain your reasoning. Now run the program. Is the output what you expected? If not, figure out why.

```c
int x[10]; int *p = x;
cout << sizeof(x)/sizeof(*x) << endl;
cout << sizeof(p)/sizeof(*p) << endl;
```

> First output is 10. Second output is undefined because `sizeof(p)` (size of pointer) varies depending on the architecture and the compiler

### Exercise 4.35

Given the following definitions,

char cval; int ival; unsigned int ui; float fval; double dval;

identify the implicit type conversions, if any, taking place:

```c
(a) cval = 'a' + 3; 'a' is promoted to int, then ('a' + 3) is converted to char
(b) fval = ui - ival * 1.0; // ival is converted to double, then that double is convert (truncated) to float
(c) dval = ui * fval; // ui is promoted to float, then the result is converted to double
(d) cval = ival + fval + dval; // ival is converted to float, then that float and fval are converted to double, then the result double is converted (truncated) to char
```

### Exercise 4.37

Rewrite each of the following old-style casts to use a named cast:

```c
int i; double d; const string *ps; char *pc; void *pv;
(a) pv = (void*)ps; // pv = static_cast<void*>(const_cast<string*>(ps));
(b) i = int(*pc); // i = static_cast<int>(*pc);
(c) pv = &d; // pv = static_cast<void*>(&d);
(d) pc = (char*) pv; // pc = static_cast<char*>(pv);
```

### Exercise 4.38

Explain the following expression:

```c
double slope = static_cast<double>(j/i);
```

> Integer division for `j/i` then cast the result to `double` and store to `slope`
