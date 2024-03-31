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

## 7.2. Access Control and Encapsulation

- *Access specifier*: enforce encapsulation with `public` and `private`
- The only difference between `class` and `struct` is the default access level: members are default `private` in `class`, and `public` in `struct`

### 7.2.1. Friends

- A class allows another class or function to access non-public members by making them a `friend`
- *Friends* are not members of the class
- Must declare a `friend` function with keyword `friend` inside a class. Good practice to also declare the `friend` function outside the class

## 7.3. Additional Class Features

### 7.3.1. Class Members Revisited (example in the book)

- Define a local name for a type member

Example:

```c
class Screen {
public:
    typedef std::string::size_type pos;

    // alternative way to declare a type member using a type alias
    // using pos = std::string::size_type;
private:
    pos cursor = 0;
};
```

7.3.2. Functions That Return `*this`

- Functions that return a reference are *lvalues*, which means they return the object itself, not a copy

Example:

```c
class Screen {
public:
    Screen &set(char);
    Screen &set(pos, pos, char);
    // other members as before
};

inline Screen &Screen::set(char c) {
    contents[cursor] = c; // set the new value at the current cursor location
    return *this; // return this object as an lvalue
}

inline Screen &Screen::set(pos r, pos col, char ch) {
    contents[r*width + col] = ch; // set specified location to given value
    return *this; // return this object as an lvalue
}
```

- A `const` member function that returns `*this` as a reference should have a return type that is a reference to `const`.

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

### Exercise 7.18

What is encapsulation? Why is it useful?

> Encapsulation is the separation of the interface and implementation. In C++, it hides the implementation details by putting the implementation in the private part of a class

> It is useful because users cannot change the state of an encapsulated object, and the implementation part can be changed without requiring changes in the user-level code

### Exercise 7.25

Can Screen safely rely on the default versions of copy and assignment? If so, why? If not, why not?

> Yes because synthesized versions of copy and assignment work correctly for classes that have vector or string members

### Exercise 7.27

Add the `move`, `set`, and `display` operations to your version of `Screen`. Test your class by executing the following code:

```c
Screen myScreen(5, 5, 'X');
myScreen.move(4,0).set('#').display(cout);
cout << "\n";
myScreen.display(cout);
cout << "\n";
```

[Code](e7_27.cpp)
```
