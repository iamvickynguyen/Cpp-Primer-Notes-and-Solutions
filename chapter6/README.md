# Chapter 6. Functions

## 6.1. Function Basics

### 6.1.1. Local Objects

- *Automatic objects*: objects that exist only while a block is executing
- *Local static objects*: are not destroyed when a function ends; they are destroyed when the program terminates
- *Arguments*: are the initializers for a function's parameters

Example:

```c
size_t count_calls() {
    static size_t ctr = 0; // value will persist across calls
    return ++ctr;
}

int main() {
    for (size_t i = 0; i != 10; ++i)
        cout << count_calls() << endl;
    return 0;
}

// Will print 1 throught 10 inclusive
```

### 6.1.3. Separate Compilation

- Separate compilation lets us split programs into several files, each of which can be compiled independently

## Exercises

### Exercise 6.1

What is the difference between a parameter and an argument?

> Parameter is defined in function declaration. An argument is an actual value that is passed in a function call.

### Exercise 6.6

Explain the differences between a parameter, a local variable, and a local static variable. Give an example of a function in which each might be useful.

> Local variable is defined inside a block. Parameter is a local variable that is defined in function parameter list. Local static variable is declared inside a block but lives throughout the program lifetime.

### Exercise 6.7

Write a function that returns 0 when it is first called and then generates numbers in sequence each time it is called again.

[Code](e6_7.cpp)

### Exercise 6.8

Write a header file named Chapter6.h that contains declarations for the functions you wrote for the exercises in § 6.1 (p. 205).

[Code](Chapter6.h)

### Exercise 6.9

Write your own versions of the fact.cc and factMain.cc files. These files should include your Chapter6.h from the exercises in the previous section. Use these files to understand how your compiler supports separate compilation.

[fact.cc](fact.cc)

[factMain.cc](factMain.cc)
