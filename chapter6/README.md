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

## 6.2. Argument Passing

- Programmers accustomed to programming in C often use pointer parameters to access objects outside a function. In C++, programmers generally use reference parameters instead

### 6.2.2. Passing Arguments by Reference

- Reference parameters that are not changed inside a function should be references to const
- Can use reference paramters to return additional information

Example:

```c
// returns the index of the first occurrence of c in s
// the reference parameter occurs counts how often c occurs
string::size_type find_char(const string &s, char c, string::size_type &occurs) {
    auto ret = s.size(); // position of the first occurrence, if any
    occurs = 0; // set the occurrence count parameter
    for (decltype(ret) i = 0; i != s.size(); ++i) {
        if (s[i] == c) {
            if (ret == s.size())
                ret = i; // remember the first occurrence of c
            ++occurs; // increment the occurrence count
        }
    }
    return ret; // count is returned implicitly in occurs
}
```

### 6.2.3. `const` Parameters and Arguments

- When copying an argument to initialize a parameter, top-level `const`s are ignored

Example:

```c
void fcn(const int i) { /* fcn can read but not write to i */ }
void fcn(int i) { /* . . . */ } // error: redefines fcn(int)
```

- Use reference to `const` when possible

### 6.2.4. Array Parameters

- We cannot copy an array, and when we use an array, it is usually converted to a pointer
- We cannot pass an array by value, but we can write a parameter that looks like:

```c
// despite appearances, these three declarations of print are equivalent
// each function has a single parameter of type const int*
void print(const int*);
void print(const int[]); // shows the intent that the function takes an array
void print(const int[10]); // dimension for documentation purposes (at best)
```

- We can call the above `print` function like:

```c
int i = 0, j[2] = {0, 1};
print(&i); // ok: &i is int*
print(j); // ok: j is converted to an int* that points to j[0]
```

- We can define a variable that is a reference to an array. This ensures that we are working with an actual array, not just a pointer, and allows us to retain the array size information

Example:

```c
void print(int (&arr)[10])
```

```c
int i = 0, j[2] = {0, 1};
int k[10] = {0,1,2,3,4,5,6,7,8,9};
print(&i); // error: argument is not an array of ten ints
print(j); // error: argument is not an array of ten ints
print(k); // ok: argument is an array of ten ints
```

- There is no multidimensional array in C++, just an array of arrays
- The compiler ignores the first dimension, so we can do:

```c
// matrix points to the first element in an array whose elements are arrays of ten ints
void print(int (*matrix)[10], int rowSize) { /* . . . */ }

// equivalent definition
void print(int matrix[][10], int rowSize) { /* . . . */ }
```

### 6.2.5. `main`: Handling Command-Line Options

- We can pass 2 optional parameters to `main` as follows:

```c
int main(int argc, char *argv[]) {/*...*/} // C-style character strings
int main(int argc, char **argv) {/*...*/} // argv points to a char*
```

### 6.2.6. Functions with Varying Parameters

- Can use `initializer_list<T>` parameter when we don't know how many arguments to pass to a function
- `initializer_list<T>` is same as `const vector<T>`

Example:

```c
void error_msg(ErrCode e, initializer_list<string> il) {
    cout << e.msg() << ": ";
    for (const auto &elem : il)
        cout << elem << " " ;
    cout << endl;
}
```

- *Ellipsis* parameters allow a function to accept a varying number of arguments of varying types that are common to both C and C++
- Objects of most class types are not copied properly when passed to an ellipsis parameter
- No type checking is done for ellipsis parameter

Example:

```c
void foo(int count, ...);
```

## 6.3. Return Types and the `return` Statement

### 6.3.1. Functions with No Return Value

- A `return` with no value may be used only in a function with return type of `void`

### 6.3.2. Functions That Return a Value

- Never return a reference or pointer to a local object as its storage is freed after a function terminates

Example:

```c
// disaster: this function returns a reference to a local object
const string &manip() {
    string ret;
    // transform ret in some way
    if (!ret.empty())
        return ret; // WRONG: returning a reference to a local object!
    else
        return "Empty"; // WRONG: "Empty" is a local temporary string
}
```

- Reference returns are lvalues. Others are rvalues

Example:

```c
char &get_val(string &str, string::size_type ix) {
    return str[ix]; // get_val assumes the given index is valid
}

int main() {
    string s("a value");
    cout << s << endl; // prints a value
    get_val(s, 0) = 'A'; // changes s[0] to A
    cout << s << endl; // prints A value
    return 0;
}
```

### 6.3.3. Returning a Pointer to an Array

- Since we can't copy an array, a function can't return an array. However, a function can return a pointer or a reference to an array
- Can use type alias to simplify syntax used to define functions that return pointers or references to arrays

Example:

```c
typedef int arrT[10]; // arrT is a synonym for the type array of ten ints
using arrtT = int[10]; // equivalent declaration of arrT; see § 2.5.1 (p. 68)
arrT* func(int i); // func returns a pointer to an array of five ints
```

- Without type alias, we must remember the dimension of an array

Example:

```c
int arr[10]; // arr is an array of ten ints
int *p1[10]; // p1 is an array of ten pointers
int (*p2)[10] = &arr; // p2 points to an array of ten ints
```

- The parameter list precedes the dimension, so the form of a function that returns a pointer to an array is `Type (*function(parameter_list))[dimension]`

Example:

```c
int (*func(int i))[10];
```

- Another way to declare `func` is using a *trailing return type* (i.e., `-> parameter list`)

Example:

```c
// fcn takes an int argument and returns a pointer to an array of ten ints
auto func(int i) -> int(*)[10];
```

- A third way is using `decltype`. Note that `decltype` doesn't automatically convert an array to a pointer type (i.e., it returns an array type), so we must add `*` to indicate that the function returns a pointer

Example:

```c
int odd[] = {1,3,5,7,9};
int even[] = {0,2,4,6,8};

// returns a pointer to an array of five int elements
decltype(odd) *arrPtr(int i) {
    return (i % 2) ? &odd : &even; // returns a pointer to the array
}
```

## 6.4. Overloaded Functions

- Functions that have the same name but different parameter lists and that appear in the same scope are *overloaded*

Example:

```c
void print(const char *cp);
void print(const int *beg, const int *end);
void print(const int ia[], size_t size);
```

- The main function may not be overloaded
- Overloading lets us avoid inventing (and remembering) nanes for common operations, but we should only overload operations that actually do similar things

Example:

```c
// Consider a set of functions that move the cursor on a Screen

// Easier to understand
Screen& moveHome();
Screen& moveAbs(int, int);
Screen& moveRel(int, int, string direction);

// Lost information that was inherent in the function names
Screen& move();
Screen& move(int, int);
Screen& move(int, int, string direction);
```

- *Function matching* (aka *overload resolution*): the process by which a particular function call is associated with a specific function from a set of overloaded functions

### 6.4.1. Overloading and Scope

- If we declare a name in an inner scope, that name hides uses of that name declared in an outer scope

Example:

```c
string read();
void print(const string &);
void print(double); // overloads the print function
void fooBar(int ival) {
    bool read = false; // new scope: hides the outer declaration of read
    string s = read(); // error: read is a bool variable, not a function
    // bad practice: usually it's a bad idea to declare functions at local scope
    void print(int); // new scope: hides previous instances of print
    print("Value: "); // error: print(const string &) is hidden
    print(ival); // ok: print(int) is visible
    print(3.14); // ok: calls print(int); print(double) is hidden
}
```

- In C++, name lookup happens before type checking.

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

### Exercise 6.10

Using pointers, write a function to swap the values of two ints. Test the function by calling it and printing the swapped values.

[Code](e6_10.cpp)

### Exercise 6.12

Rewrite the program from exercise 6.10 in § 6.2.1 (p. 210) to use references instead of pointers to swap the value of two ints. Which version do you think would be easier to use and why?

[Code](e6_12.cpp)

> This version is easier to use because shorter syntax

### Exercise 6.16

The following function, although legal, is less useful than it might be. Identify and correct the limitation on this function:

```c
bool is_empty(string& s) { return s.empty(); }
```

> Since the function doesn't modify the string, can add `const`; Otherwise we cannot pass a `const string` to this function. Fix: `bool is_empty(const string &s) { return s.empty(); }`

### Exercise 6.18

Write declarations for each of the following functions. When you write these declarations, use the name of the function to indicate what the function does.

(a) A function named compare that returns a bool and has two parameters
that are references to a class named matrix.

```c
bool compare(const Matrix &a, const Matrix &b);
```

(b) A function named change\_val that returns a vector\<int> iterator
and takes two parameters: One is an int and the other is an iterator for a
vector\<int>.

```c
vector<int>::iterator change_val(int x, vector<int>::iterator &iter);
```

### Exercise 6.20

When should reference parameters be references to const? What happens if we make a parameter a plain reference when it could be a reference to const?

> Reference parameters should be references to const when the function doesn't change the objects' values. Compile error if we make a parameter a plain reference when it should be a reference to const

### Exercise 6.21

Write a function that takes an int and a pointer to an int and returns the larger of the int value or the value to which the pointer points. What type should you use for the pointer?

```c
int get_larger(const int a, const int *b) {
    return (a > *b) ? a : (*b);
}
```

### Exercise 6.24

Explain the behavior of the following function. If there are problems in the code, explain what they are and how you might fix them.

```c
void print(const int ia[10])
{
    for (size_t i = 0; i != 10; ++i)
        cout << ia[i] << endl;
}
```

> Since the array is converted to a pointer, including the size in the array parameter is irrelevant. In this case, `const int ia[10]` is same as `const int ia[1]` and `const int ia[100]` as all of them are converted into `const int *ia`. If we want the size then we can pass a reference: `void print(const int (&ia)[10]) {/*...*/}`

### Exercise 6.29

When you use an initializer\_list in a range for would you ever use a reference as the loop control variable? If so, why? If not, why not?

> Depending on the type, if it is a POD-type, we don't need reference because POD is cheap to copy (such as int). Otherwise, we should use reference or const reference

### Exercise 6.31

When is it valid to return a reference? A reference to const?

> It is valid to return a reference when you refer to a pre-existed object. A reference to const when you don't want the pre-existed object to be modified

### Exercise 6.32

Indicate whether the following function is legal. If so, explain what it does; if not, correct any errors and then explain it.

```c
int &get(int *arry, int index) { return arry[index]; }
int main() {
    int ia[10];
    for (int i = 0; i != 10; ++i)
        get(ia, i) = i;
}
```
> Legal, the program assign value from 0 to 9 to `arry`

### Exercise 6.35

In the call to fact, why did we pass val - 1 rather than val--?

> Because the recursive function will use val before it is decremented. This leads to an infinite loop

### Exercise 6.36

Write the declaration for a function that returns a reference to an array of ten strings, without using either a trailing return, decltype, or a type alias.

```c
string (&get_string_array())[10];
```

### Exercise 6.37

Write three additional declarations for the function in the previous exercise. One should use a type alias, one should use a trailing return, and the third should use decltype. Which form do you prefer and why?

```c
// type alias
using arrT = string[10];
arrT& get_string_array();
```

```c
// trailing return
auto get_string_array() -> string(&)[10];
```

```c
// decltype
string arr[10];
decltype(arr) &get_string_array();
```

> I prefer type alias because it is easy to understand

### Exercise 6.38

Revise the arrPtr function on to return a reference to the array.

```c
decltype(odd) &arrPtr(int i) {
    return (i % 2) ? odd : even;
}
```

### Exercise 6.39

Explain the effect of the second declaration in each one of the following sets of declarations. Indicate which, if any, are illegal.

```c
(a) int calc(int, int);
    int calc(const int, const int);
```

> Legal

```c
(b) int get();
    double get();
```

> Illegal, only return type is different

```c
(c) int *reset(int *);
    double *reset(double *);
```

> Legal, parameter type is different
