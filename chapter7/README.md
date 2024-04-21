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

### 7.3.2. Functions That Return `*this`

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

### 7.3.4 Friendship Revisited

- A class can make another class as its friend or it can make some specific member functions of another class as friends.

Example:

```c
// Example of making a class as a friend

class Screen {
    // Window_mgr members can access the private parts of class Screen
    friend class Window_mgr;
    // ... rest of the Screen class
};

class Window_mgr {
public:
    // location ID for each screen on the window
    using ScreenIndex = std::vector<Screen>::size_type;

    // reset the Screen at the given position to all blanks
    void clear(ScreenIndex);

private:
    std::vector<Screen> screens {Screen(24, 80, ' ')};
};

void Window_mgr::clear(ScreenIndex i) {
    // s is a reference to the Screen we want to clear
    Screen &s = screens[i];
    // reset the content of that Screen to all blanks
    s.contents = string(s.height * s.width, ' ');
}
```

```c
// Example of making a member function a friend

class Screen {
    // Window_mgr::clear must have been declared before class Screen
    friend void Window_mgr::clear(ScreenIndex);
    // ... rest of the Screen class
};
```

## 7.4. Class Scope

- Every class has its own scope
- Outside the class scope, ordinary data and function members may be accessed through an object, a reference, or a pointer using a *member access operator* (see 4.6).

### 7.4.1. Name Lookup and Class Scope

- Class definitions are processed in 2 stages:
    1. The member declarations are compiled
    2. Then, the function bodies are compiled 
- A name used in the body of a member function is resolved as follows:
    1. First, look for a declaration of the name inside the member function
    2. If not found, look for a declaration inside the class
    3. If not found, look for a declaration that is in the scope before the member function definition
- It is a bad practice to use a same name for a parameter and a member.

Example:

```c
// For illustration purposes. This is a bad practice.

int height;

class Screen {
public:
    typedef std::string::size_type pos;
    void dummy_fn(pos height) {
        cursor = width * height; // which height? the parameter
    }

private:
    pos cursor = 0;
    pos height = 0, width = 0;
};
```

- In the example above, the `height` parameter hides the member named `height`. To override the normal lookup rules, we can do:

```c
void Screen::dummy_fn(pos height) {
    cursor = width * this->height; // member height

    // alternative way to indicate the member
    cursor = width * Screen::height; // member height
}
```

- If we want the name from the outer scope, we can use the *scope operator*

```c
// Bad practice. Don't hide names that are needed from surrounding scopes
void Screen::dummy_fn(pos height) {
    cursor = width * ::height; // which height? the global one
}
```

## 7.5. Constructors Revisited

### 7.5.1. Constructor Initializer List

- We can often ignore the distinction between whether a member is initialized or assigned.
- Members that are `const` or *references* must be initialized.
- Members of a class type that does not define a default constructor must be initialized.

Example:

```c
class ConstRef {
public:
    ConstRef (int ii);
private:
    int i;
    const int ci;
    int &ri;
};
```

```c
ConstRef::ConstRef (int ii) {
    i = ii; // ok
    ci = ii; // error: cannot assign to a const
    ri = i; // error: ri was never initialized
}

// Note: by the time the body of the constructor begins executing, initialization is complete.
```

```c
// ok: explicitly initialize reference and const members
ConstRef::ConstRef (int ii): i(ii), ci(ii), ri(i) {}
```

- **Best practice**: write constructor initializers in the same order as the members are declared. When possible, avoid using members to initialize other members.

Example:

```c
class X {
    int i;
    int j;
public:
    // undefined: i is initialized before j
    X (int val): j(val), i(j) {}
};
```

### 7.5.3. The Role of the Default Constructor

- *Default constructor* is used automatically when an object is default or value initialized.
- Default initialization happens when:
    - We define *nonstatic* variables (section 2.2.1) or arrays at block scope without initializers
    - A class has members of class type uses the *synthesized default constructor* (section 7.1.4)
    - Class members are not explicitly initialized in a *constructor initializer list* (section 7.1.4)
- Value initialization happens:
    - During array initialization when we provide fewer initializers than the size of the arrays
    - When we define a local static object without an initializer (section 6.1.1)
    - When we explicitly request value initialization by writing an expression of the form `T()`, where `T` is the name of a type (i.e., `vector`)

Example:

```c
class NoDefault {
public:
    NoDefault (const std::string&);
    // additional members follow, but no other constructors
};

struct A {
    NoDefault my_mem;
};

A a; // error: cannot synthesize a constructor for A

struct B {
    B() {} // error: no initializer for b_member
    NoDefault b_member;
};
```

### 7.5.4. Implicit Class-Type Conversions

- A constructor that can be called with a single argument defines an implicit conversion from the constructor's parameter type to the class type.

Example:

```c
string null_book = "9-999-9999";

// constructs a temporary Sales_data object
// with units_sold and revenue are 0 and bookNo equal to null_book
item.combine(null_book);

// Since combine's parameter is a reference to const, we can pass a temporary to that parameter
```

- Suppress implicit conversions defined by constructors with `explicit` keyword.

Example:

```c
class Sales_data {
public:
    Sales_data() = default;
    Sales_data(const std::string &s, unsigned n, double p): bookNo(s), units_sold(n), revenue(p * n) {}
    explicit Sales_data(const std::string &s): bookNo(s) {}
    explicit Sales_data(std::istream&);
    // remaining members as before
}
```

```c
item.combine(null_book); // error: string constructor is explicit
item.combine(cin); // error: istream constructor is explicit
```

- Force a conversion

Example:

```c
// ok: the argument is an explicit constructed Sales_data object
item.combine(Sales_data(null_book));

// ok: static_cast can use an explicit constructor
item.combine(static_cast<Sales_data>(cin));
```

### 7.5.5. Aggregate Classes

- An *aggregate class* gives users direct access to its members and has special initialization syntax.
- A class is an aggregate if:
    - All data members are `public`
    - No constructors
    - No in-class initializers (section 2.6.1)
    - No base classes or `virtual` functions

Example:

```c
struct Data {
    int ival;
    string s;
};

// val1.ival = 0; val1.s = string("Anna")
Data val1 = { 0, "Anna" };

// error: can't use "Anna" to initialize ival, or 1024 to initialize s
Data val2 = { "Anna", 1024 };
```

- Drawbacks:
    - Require all members to be `public`
    - Users must correctly initialize every member of every object -> tedious and error-prone
    - If a member is added or removed, all initializations have to be updated

### 7.5.6. Literal Classes

- Parameters and return type of a `constexpr` function must be literal types.
- An *aggregate* class whose data members are all of literal type is a *literal* class.
- A *non-aggregate* class, the meets the following restrictions, is also a *literal* class:
    - All data members mst have literal type
    - The class must have at least 1 `constexpr` constructor
    - If a data member has an in-class initializer, the initializer for a member of built-in type must be a constant expression or if the member has a class type, the initializer must use the member own's `constexpr` constructor
    - The class must use default definition for its destructor, which is the member that *destroys* objects of the class type

#### `constexpr` Constructors

- A `constexpr` constructor can be declared as `= default` (or as a deleted function, section 13.1.6)
- The body of a `constexpr` constructor is typically empty

Example:

```c
class Debug {
public:
    constexpr Debug(bool b = true): hw(b), io(b), other(b) {}
    constexpr Debug(bool h, bool i, bool o): hw(h), io(i), other(o) {}
    constexpr bool any() { return hw || io || other; }
    void set_io(bool b) { io = b; }
    void set_hw(bool b) { hw = b; }
    void set_other(bool b) { hw = b; }

private:
    bool hw; // hardware errors other than IO errors
    bool io; // IO errors
    bool other; // other errors
};
```

- A `constexpr` constructor must initialize every data member.
- The initializers must either use a `constexpr` constructor or be a constant expression.
- A `constexpr` constructor is used to generate `constexpr` objects that are `constexpr` and for parameters or return types in `constexpr` function.

Example:

```c
constexpr Debug io_sub(false, true, false); // debugging IO
if (io_sub.any())
    cerr << "print error messages" << endl;

constexpr Debug prod(false); // no debugging during production
if (prod.any())
    cerr << "print an error message" << endl;
```

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

### Exercise 7.28

What would happen in the previous exercise if the return type of `move`, `set`, and `display` was `Screen` rather than `Screen&` ?

> Our object won't change 

### Exercise 7.31

Define a pair of classes X and Y, in which X has a pointer to Y, and Y has an object of type X.

```c
class X {
public:
    Y *y;    
};

class Y {
public:
    X x;
};
```

### Exercise 7.34

What would happen if we put the `typedef` of `pos` in the `Screen` class on page 285 as the last line in the class?

> There would be an error: unknow type name pos

### Exercise 7.35

Explain the following code, indicating which definition of `Type` or `initVal` is used for each use of those names. Say how you would fix any errors.

```c
typedef string Type;
Type initVal(); // string

class Exercise {
public:
	typedef double Type;
	Type setVal(Type); // double
	Type initVal(); // double

private:
	int val;
};

Type Exercise::setVal (Type parm) { // string, double
	val = parm + initVal(); // Exercise::initVal()
	return val;
}
```

Fix: change to `Exercise::Type`. Changing names would be a good solution as well.

```c
typedef string Type;
Type initVal();

class Exercise {
public:
	typedef double Type;
	Type setVal(Type);
	Type initVal();

private:
	int val;
};

Exercise::Type Exercise::setVal (Type parm) {
	val = parm + initVal();
	return val;
}
```

### Exercise 7.38

We might want to supply `cin` as a default argument to the constructor that takes an `istream&`. Write the constructor declaration that uses `cin` as a default argument.

```c
class Sales_data {
public:
    Sales_data (std::istream &is = std::cin) {
        read(is, *this);
    }
};
```

### Exercise 7.39

Would it be legal for both the constructor that takes a `string` and the one that takes an `istream&` to have default arguments? If not, why not?

> Illegal, because the call of overloaded `Sales_data()` is ambiguous.

### Exercise 7.43

Assume we have a class named `NoDefault` that has a constructor that takes an `int`, but has no default constructor. Define a class `C` that has a member of type `NoDefault`. Define the default constructor for `C`.

```c
class NoDefault {
public:
    NoDefault (int) {}
};

class C {
public:
    C(): c_mem(0) {}

private:
    NoDefault c_mem;
};
```

### Exercise 7.44

Is the following declaration legal? If not, why not? `vector<NoDefault> vec(10);`

> No, because there is no default constructor for each of the 10 `NoDefault` elements. 

### Exercise 7.45

What if we defined the vector in the previous exercise to hold objects of type `C`?

> Ok, because there is a default constructor for `C`

### Exercise 7.47

Explain whether the `Sales_data` constructor that takes a string should be `explicit`. What are the benefits of making the constructor `explicit`? What are the drawbacks?

> It depends on "how we think our usedrs will use the conversion" (textbook)

> **Pros**: Prevent the use of constructors in a context that requires implicit conversions

> **Cons**: Meaningful only on constructors that can be called with a single argument

### Exercise 7.50

Determine whether any of your Person class constructors should be explicit.

```c
explicit Person(std::istream &is) { read(is, *this); }
```

### Exercise 7.51

Why do you think `vector` defines its single-argument constructor as `explicit`, but `string` does not?

> - `int getSize(const std::vector<int>&);` : if `vector` doesn't define its single-argument constructor, we can do `getSize(10)`. This is confusing.

> - `void setName(std::string);` : we can use `std::string` to replace `const char*` when we call `setName("Vicky");`

### Exercise 7.54

Should the members of `Debug` that begin with `set_` be declared as constexpr? If not, why not?

> Cannot, because `constexpr` member functions are implicitly `const`.

### Exercise 7.55

Is the `Data` class from §7.5.5(p. 298) a literal class? If not, why not? If so, explain why it is literal.

> No, because `std::string` isn't a literal type.
