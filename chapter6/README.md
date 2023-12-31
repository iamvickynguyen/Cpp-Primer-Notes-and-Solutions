# Chapter 6. Functions

<!-- vim-markdown-toc GFM -->

* [6.1. Function Basics](#61-function-basics)
    * [6.1.1. Local Objects](#611-local-objects)
    * [6.1.3. Separate Compilation](#613-separate-compilation)
* [6.2. Argument Passing](#62-argument-passing)
    * [6.2.2. Passing Arguments by Reference](#622-passing-arguments-by-reference)
    * [6.2.3. `const` Parameters and Arguments](#623-const-parameters-and-arguments)
    * [6.2.4. Array Parameters](#624-array-parameters)
    * [6.2.5. `main`: Handling Command-Line Options](#625-main-handling-command-line-options)
    * [6.2.6. Functions with Varying Parameters](#626-functions-with-varying-parameters)
* [6.3. Return Types and the `return` Statement](#63-return-types-and-the-return-statement)
    * [6.3.1. Functions with No Return Value](#631-functions-with-no-return-value)
    * [6.3.2. Functions That Return a Value](#632-functions-that-return-a-value)
    * [6.3.3. Returning a Pointer to an Array](#633-returning-a-pointer-to-an-array)
* [6.4. Overloaded Functions](#64-overloaded-functions)
    * [6.4.1. Overloading and Scope](#641-overloading-and-scope)
* [6.5. Features for Specialized Uses](#65-features-for-specialized-uses)
    * [6.5.1. Default Arguments](#651-default-arguments)
    * [6.5.2. Inline and `constexpr` Functions](#652-inline-and-constexpr-functions)
    * [6.5.3. Aids for Debugging](#653-aids-for-debugging)
* [6.6. Function Matching](#66-function-matching)
    * [6.6.1. Argument Type Conversions](#661-argument-type-conversions)
* [6.7. Pointers to Functions](#67-pointers-to-functions)
* [Exercises](#exercises)
    * [Exercise 6.1](#exercise-61)
    * [Exercise 6.6](#exercise-66)
    * [Exercise 6.7](#exercise-67)
    * [Exercise 6.8](#exercise-68)
    * [Exercise 6.9](#exercise-69)
    * [Exercise 6.10](#exercise-610)
    * [Exercise 6.12](#exercise-612)
    * [Exercise 6.16](#exercise-616)
    * [Exercise 6.18](#exercise-618)
    * [Exercise 6.20](#exercise-620)
    * [Exercise 6.21](#exercise-621)
    * [Exercise 6.24](#exercise-624)
    * [Exercise 6.29](#exercise-629)
    * [Exercise 6.31](#exercise-631)
    * [Exercise 6.32](#exercise-632)
    * [Exercise 6.35](#exercise-635)
    * [Exercise 6.36](#exercise-636)
    * [Exercise 6.37](#exercise-637)
    * [Exercise 6.38](#exercise-638)
    * [Exercise 6.39](#exercise-639)
    * [Exercise 6.40](#exercise-640)
    * [Exercise 6.41](#exercise-641)
    * [Exercise 6.43](#exercise-643)
    * [Exercise 6.46](#exercise-646)
    * [Exercise 6.48](#exercise-648)
    * [Exercise 6.52](#exercise-652)
    * [Exercise 6.53](#exercise-653)
    * [Exercise 6.54](#exercise-654)
    * [Exercise 6.55](#exercise-655)
    * [Exercise 6.56](#exercise-656)

<!-- vim-markdown-toc -->

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

## 6.5. Features for Specialized Uses

### 6.5.1. Default Arguments

- *Default argument*: some parameters of a function have given values
- Functions with default arguments can be called with or without that argument 

Example:

```c
void foo(int a, string b = "hello") {/*...*/}
```

### 6.5.2. Inline and `constexpr` Functions

- Function call is slower than evaluating the equivalent expression
- Function call does a lot of work: registers are saved before the call and restored after the return; arguments may be copied; and the program branches to a new location
- *Inline* functions avoid function call overhead. The program will copy the function and paste to the places the function is called
- The inline specification is only a request to the compiler. The compiler may choose to ignore this request
- *Inline* mechanism is meant to optimize small, straight-line functions that are called frequently. Many compilers won't inline a recursive function

Example:

```c
inline shorterString(string &a, string &b) {/*...*/}
cout << shorterString(s1, s2) << endl;

// during compilation, it will be expanded into
cout << (s1.size() < s2.size() ? s1 : s2) << endl;
```

- `constexpr` function: a function that can be used in a constant expression
- A `constexpr` function must meet certain criteria:
    - The return type and the type of each parameter must be a literal type
    - The function body must contain exactly 1 return statement

Example:

```c
constexpr int new_sz() { return 42; }
constexpr int foo = new_sz(); // ok: foo is a constant expression
```

- `constexpr` function can return a non-constant value

Example:

```c
// scale(arg) is a constant expression if arg is a constant expression
constexpr size_t scale(size_t cnt) { return new_sz() * cnt; }
```

- A `constexpr` function is not required to return a constant expression
- `inline` and `constexpr` functions normally are defined in headers

### 6.5.3. Aids for Debugging

- `assert` and `NDEBUG`
- If `NDEBUG` is defined, `assert` does nothing

## 6.6. Function Matching

- *Candidate function*: a function in the overloaded functions set. Has the same name as the called function and is visible at the point of the call
- *Viable function*: a function, from the set of candidate functions, that has the same number of parameters as the arguments in the call, and same each type must match
- Function matching determines which viable function is the "best" match
- The overall best match is the one and only one function which:
    - The match for each argument is no worse than the match required by any other viable function
    - There is >= 1 argument for which the match is better than the match provided by any other viable function

Example:

```c
f(int, int);
f(double, double);
f(42, 2.56); // compiler will reject this call because it's ambiguous
```

- Casts should not be needed to call an overloaded function. The need for a cast suggests that the parameter sets are designed poorly

### 6.6.1. Argument Type Conversions

- To determine the best match, the compiler ranks the conversions as follows:
    1. An exact match
        - The argument and parameter types are identical
        - The argument is converted from an array or function type to the corresponding pointer type
        - A top-level `const` is added to or discarded fromt the argument
    2. Match through a `const` conversion
    3. Match through a promotion
    4. Match through an arithmetic or pointer conversion
    5. Match through a class-type conversion
- Promotions and conversions among the built-in types can yield surprising results in the context of function matching. Well-designed systems rarely include functions with similar parameters

Example:

```c
// Matches requiring promotion or arithmetic conversion
void ff(int);
void ff(short);
ff('a'); // char promotes to int; calls f(int)

void manip(long);
void manip(float);
manip(3.14); // error: ambiguous call
             // 3.14 is a double, which can be converted to either long or float
```

```c
// Matches with const arguments
Record lookup(Account&); // function that takes a reference to Account
Record lookup(const Account&); // new function that takes a const reference
const Account a;
Account b;
lookup(a); // calls lookup(const Account&)
lookup(b); // calls lookup(Account&)
```

## 6.7. Pointers to Functions

- A function pointer is a pointer that denotes a function

Example:

```c
// pf points to a function returning bool that takes two const string references
bool (*pf)(const string &, const string &); // uninitialized
```

- When using the name of a function as a value, the function is automatically converted to a pointer

Examples:

```c
pf = lengthCompare; // pf now points to the function named lengthCompare
pf = &lengthCompare; // equivalent assignment: address-of operator is optional
```

```c
bool b1 = pf("hello", "goodbye"); // calls lengthCompare
bool b2 = (*pf)("hello", "goodbye"); // equivalent call
bool b3 = lengthCompare("hello", "goodbye"); // equivalent call
```

- When declaring a pointer to an overloaded function, the compiler uses the type of the pointer to determine which overloaded function to use

Example:

```c
void ff(int*);
void ff(unsigned int);
void (*pf1)(unsigned int) = ff; // pf1 points to ff(unsigned)
```

```c
void (*pf2)(int) = ff; // error: no ff with a matching parameter list
double (*pf3)(int*) = ff; // error: return type of ff and pf3 don't match
```

- We cannot define parameters of function type, but can have a parameter that is a pointer to function

Example:

```c
// third parameter is a function type and is automatically treated as a pointer to function
void useBigger(const string &s1, const string &s2,
    bool pf(const string &, const string &));
// equivalent declaration: explicitly define the parameter as a pointer to function
void useBigger(const string &s1, const string &s2,
    bool (*pf)(const string &, const string &));
```

```c
// automatically converts the function lengthCompare to a pointer to function useBigger(s1, s2, lengthCompare);
```

- Type aliases and `decltype` help simplify code

Example:

```c
// Func and Func2 have function type
typedef bool Func(const string&, const string&);
typedef decltype(lengthCompare) Func2; // equivalent type

// FuncP and FuncP2 have pointer to function type
typedef bool(*FuncP)(const string&, const string&);
typedef decltype(lengthCompare) *FuncP2; // equivalent type

// equivalent declarations of useBigger using type aliases
void useBigger(const string&, const string&, Func);
void useBigger(const string&, const string&, FuncP2);
```

- We cannot return a function, but can return a pointer to a function

Example:

```c
using F = int(int*, int); // F is a function type, not a pointer
using PF = int(*)(int*, int); // PF is a pointer type
```

```c
PF f1(int); // ok: PF is a pointer to function; f1 returns a pointer to function
F f1(int); // error: F is a function type; f1 can't return a function
F *f1(int); // ok: explicitly specify that the return type is a pointer to function

// can also declare f1 directly
int (*f1(int))(int*, int);
auto f1(int) -> int (*)(int*, int); // similar, using trailing return
```

- `decltype` returns a function type, not a pointer to function type. Thus, we must add a `*`

Example:

```c
string::size_type sumLength(const string&, const string&);
string::size_type largerLength(const string&, const string&);

// depending on the value of its string parameter,
// getFcn returns a pointer to sumLength or to largerLength
decltype(sumLength) *getFcn(const string &);
```

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

### Exercise 6.40

Which, if either, of the following declarations are errors? Why?

```c
(a) int ff(int a, int b = 0, int c = 0); // ok
(b) char *init(int ht = 24, int wd, char bckgrnd); // error, missing default values for 'wd' and 'bckgrnd'
```

### Exercise 6.41

Which, if any, of the following calls are illegal? Why? Which, if any, are legal but unlikely to match the programmer’s intent? Why?

```c
char *init(int ht, int wd = 80, char bckgrnd = ' ');
(a) init(); // illegal, missing parameter 'ht'
(b) init(24,10); // legal
(c) init(14, '*'); // legal but not match the intention, should call init(14, 80, '*')
```

### Exercise 6.43

Which one of the following declarations and definitions would you put in a header? In a source file? Explain why.

```c
(a) inline bool eq(const BigInt&, const BigInt&) {...}
(b) void putValues(int *arr, int size);
```

> I will put both in a header file because (a) is an inline function and (b) is a function declaration. They normally are defined in the header

### Exercise 6.46

Would it be possible to define isShorter as a constexpr? If so, do so. If not, explain why not.

> No, because a `constexpr` function must not take runtime actions. However, `std::string::size()` is not a constant expression

### Exercise 6.48

Explain what this loop does and whether it is a good use of assert:

```c
string s;
while (cin >> s && s != sought) { } // empty body
assert(cin);
```

> The loop keeps reading input until it is sought. It isn't a good use of assert because assert will always happen when a user inputs EOF directly. Using `(assert(!cin || s == sought))` is better.

### Exercise 6.52

Given the following declarations,

void manip(int, int);
double dobj;

what is the rank (§ 6.6.1, p. 245) of each conversion in the following calls?

```c
(a) manip('a', 'z'); // rank 3, promotion
(b) manip(55.4, dobj); // rank 4, arithmetic conversion
```

### Exercise 6.53

Explain the effect of the second declaration in each one of the following sets of declarations. Indicate which, if any, are illegal.

```c
(a) int calc(int&, int&);
    int calc(const int&, const int&); // legal

(b) int calc(char*, char*);
    int calc(const char*, const char*); // legal

(c) int calc(char*, char*);
    int calc(char* const, char* const); // illegal, top-level const is omit
```

### Exercise 6.54

Write a declaration for a function that takes two int parameters and returns an int, and declare a vector whose elements have this function pointer type.

```c
int f(int a, int b);

vector<int(*)(int, int)> vec1;

using pf = decltype(f)*;
vector<pf> vec2;
```

### Exercise 6.55

Write four functions that add, subtract, multiply, and divide two int values. Store pointers to these values in your vector from the previous exercise.

```c
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int div(int a, int b) { return b != 0 ? a / b : 0; }

vec1.push_back(add);
vec1.push_back(sub);
vec1.push_back(mul);
vec1.push_back(div);
```

### Exercise 6.56

Call each element in the vector and print their result.

```c
for (auto f: vec1) std::cout << f(1, 2) << '\n';
```
