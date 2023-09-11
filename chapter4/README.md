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

## Exercises

### Exercise 4.3

Order of evaluation for most of the binary operators is left undefined to give the compiler opportunities for optimization. This strategy presents a trade-off between efficient code generation and potential pitfalls in the use of the language by the programmer. Do you consider that an acceptable trade-off? Why or why not?

> Yes, but programmers have to be careful. Performance in C++ is important, so compiler's features are good. However, we also don't want bugs, so it's best to avoid undefined behaviours. For example, `cout << i << ++i` should not appear in the code.
