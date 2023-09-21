# Chapter 5. Statements

- Good idea to use tools to automatically indent source code
- *Jump* statements have one of the 4 keywords: `break`, `continue`, `goto`, `return`
- Best practice is to avoid using `goto` because it makes the program hard to understand and hard to modify
- Exceptions are run time anomalies. Exception handling involves:
    - `throw` expressions: detect something it can't handle. We say a `throw` *raises* an exception
    - `try` blocks: deal with an exception. It has >= 1 `catch` clauses
        - `catch` clauses are aka *exception handlers*
    - *exception classes*: used to pass information about what happened between a `throw` and a `catch`
- Writing exception safe code is hard. Some programs use exceptions simply to terminate. However, programs that handle exceptions and continue processing must ensure objects are valid, resources don't leak, and program is restored to an appropriate state

<!-- vim-markdown-toc GFM -->

* [Exercises](#exercises)
    * [Exercise 5.4](#exercise-54)
    * [Exercise 5.8](#exercise-58)
    * [Exercise 5.13](#exercise-513)
    * [Exercise 5.15](#exercise-515)
    * [Exercise 5.19](#exercise-519)
    * [Exercise 5.23](#exercise-523)
    * [Exercise 5.24](#exercise-524)
    * [Exercise 5.25](#exercise-525)

<!-- vim-markdown-toc -->

## Exercises

### Exercise 5.4

Explain each of the following examples, and correct any problems you detect.

```c
(a) while (string::iterator iter != s.end()) { /* ... */ } 
```

```c
// Error: illegal declaration
// Fix:
string::iterator iter = s.begin();
while (iter != s.end()) {/* ... */ }
```

```c
(b) while (bool status = find(word)) { /* . . . */ }
if (!status) { /* ... */ }
```

```c
// Error: status is not defined
// Fix:
bool status;
while (status = find(word)) {/* ... */}
if (!status) {/* ... */}
```

### Exercise 5.8

What is a “dangling else”? How are else clauses resolved in C++?

> "Dangling else" is the problem when processing nested if when there are more "if"s than "else"s. In C++, an "if" is always paired with an "else".

### Exercise 5.13

Each of the programs in the highlighted text on page 184 contains a common programming error. Identify and correct each error.

```c
(a) unsigned aCnt = 0, eCnt = 0, iouCnt = 0;
char ch = next_text();
switch (ch) {
    case 'a': aCnt++;
    case 'e': eCnt++;
    default: iouCnt++;
}
```

```c
// Error: all aCnt, eCnt, iouCnt will be incremeted
// Fix:
unsigned aCnt = 0, eCnt = 0, iouCnt = 0;
char ch = next_text();
switch (ch) {
    case 'a': aCnt++; break;
    case 'e': eCnt++; break;
    default: iouCnt++;
}
```

```c
(b) unsigned index = some_value();
switch (index) {
    case 1:
        int ix = get_value();
        ivec[ ix ] = index;
        break;
    default:
        ix = ivec.size()-1;
        ivec[ ix ] = index;
}
```

```c
// Error: ix in default case is not defined
// Fix:
unsigned index = some_value();
int ix;
switch (index) {
    case 1:
        ix = get_value();
        ivec[ ix ] = index;
        break;
    default:
        ix = ivec.size()-1;
        ivec[ ix ] = index;
}
```

```c
(c) unsigned evenCnt = 0, oddCnt = 0;
int digit = get_num() % 10;
switch (digit) {
    case 1, 3, 5, 7, 9:
        oddcnt++;
        break;
    case 2, 4, 6, 8, 10:
        evencnt++;
        break;
}
```

```c
// Error: syntax error for case statements
// Fix:
unsigned evenCnt = 0, oddCnt = 0;
int digit = get_num() % 10;
switch (digit) {
    case 1: case 3: case 5: case 7: case 9:
        oddCnt++;
        break;
    case 2: case 4: case 6: case 8: case 10:
        evenCnt++;
        break;
}
```

```c
(d) unsigned ival=512, jval=1024, kval=4096;
unsigned bufsize;
unsigned swt = get_bufCnt();
switch(swt) {
    case ival:
        bufsize = ival * sizeof(int);
        break;
    case jval:
        bufsize = jval * sizeof(int);
        break;
    case kval:
        bufsize = kval * sizeof(int);
        break;
}
```

```c
// Error: case label must be a constant
// Fix:
const unsigned ival=512, jval=1024, kval=4096;
unsigned bufsize;
unsigned swt = get_bufCnt();
switch(swt) {
    case ival:
        bufsize = ival * sizeof(int);
        break;
    case jval:
        bufsize = jval * sizeof(int);
        break;
    case kval:
        bufsize = kval * sizeof(int);
        break;
}
```

### Exercise 5.15

Explain each of the following loops. Correct any problems you detect.

```c
(a) for (int ix = 0; ix != sz; ++ix) { /* ... */ }
if (ix != sz)
// . . .
```

> It tries to loop from `ix = 0` to `ix != sz`. However, `ix` is not defined outside of for loop

```c
// Fix:
int ix;
for (ix = 0; ix != sz; ++ix) {/* ... */}
if (ix != sz)
// ...
```

```c
(b) int ix;
for (ix != sz; ++ix) { /* ... */ }
```

> The loop tries to run from `ix` to `sz`. Error, missing statement in for loop

```c
// Fix:
int ix;
for (; ix < sz; ++ix) { /* ... */ }
```

```c
(c) for (int ix = 0; ix != sz; ++ix, ++ sz) { /* ... */ }
```

> It tries to loop from `ix = 0` until `ix != sz`. However, this is an infinite loop as `ix` and `sz` keep incrementing by 1

```c
// Fix:
for (int ix = 0; ix != sz; ++ix) {/* ... */}
```

### Exercise 5.19

Write a program that uses a do while loop to repetitively request two strings from the user and report which string is less than the other.

```c
string s1, s2;
cin >> s1 >> s2;
do {
    if (s1 < s2) cout << s1 << " is less than " << s2 << '\n';
    else cout << s2 << " is less than or equal to " << s1 << '\n';
} while (cin >> s1 >> s2);
```

### Exercise 5.23

Write a program that reads two integers from the standard input and prints the result of dividing the first number by the second.

[Code](e5_23.cpp)

### Exercise 5.24

Revise your program to throw an exception if the second number is zero. Test your program with a zero input to see what happens on your system if you don’t catch an exception.

[Code](e5_24.cpp)

### Exercise 5.25

Revise your program from the previous exercise to use a try block to catch the exception. The catch clause should print a message to the user and ask them to supply a new number and repeat the code inside the try.

[Code](e5_25.cpp)
