# Chapter 7. Classes

## 7.1. Defining Abstract Data Types

### 7.1.2. Defining the Revised Sales\_data Class

- Functions defined in a class are implicitly `inline`
- Objects that are `const`, and references or pointers to `const` objects, may call only `const` member functions

### 7.1.4. Constructors

- *Default constructor*: constructor with no argument
- *Synthesized default constructor*: default constructor that the compiler generates 
- Classes that have built-in or compound type rely on the synthesized default constructor only if all such members have in-class initializers
- Use `= default` if we want a default constructor and other constructors

Example:

```c
Sales_data() = default;
```

- *Constructor initializer list*: directly initializes values for data members
    - Avoiding default construction and assignment
    - For `const` and reference members, initialization must be done in the initializer list since they cannot be assigned values in the constructor body

Example:

```c
Sales_data(const std::string &s, unsigned n, double p):
    bookNo(s), units_sold(n), revenue(p*n) { }
```

### 7.1.5. Copy, Assignment, and Destruction

- Although the compiler will synthesize the copy, assignment, and destruction operations, for some classes the default versions do not behave appropriately (ie., synthesized versions may not work correctly for classes that allocate resources the reside outside the class objects)

## Exercises

### Exercise 7.4

Write a class named Person that represents the name and address of a person. Use a string to hold each of these elements. Subsequent exercises will incrementally add features to this class.

[Code](e7_4.cpp)

### Exercise 7.5

Provide operations in your Person class to return the name and address. Should these functions be const? Explain your choice.

[Code](e7_5.cpp)

> Yes they should be `const` because the functions don't modify the strings

### Exercise 7.10

What does the condition in the following if statement do?

```c
if (read(read(cin, data1), data2))
```

> It reads a string into `data1` then read another string to `data2`. The `if` condition reads 2 strings at one time
