# Chapter 5. Statements

- Good idea to use tools to automatically indent source code

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
