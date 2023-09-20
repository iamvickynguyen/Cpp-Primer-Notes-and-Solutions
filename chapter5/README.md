# Chapter 5. Statements

- Good idea to use tools to automatically indent source code

## Exercises

### Exercise 5.4

Explain each of the following examples, and correct any problems you detect.

```c
(a) while (string::iterator iter != s.end()) { /* ... */ } // illegal declaration

/*
Fix:
string::iterator iter = s.begin();
while (iter != s.end()) {/* ... */ }
*/
```

```c
(b) while (bool status = find(word)) { /* . . . */ }
if (!status) { /* ... */ } // status is not defined

/*
Fix:
bool status;
while (status = find(word)) {/* ... */}
if (!status) {/* ... */}
*/
```

### Exercise 5.8

What is a “dangling else”? How are else clauses resolved in C++?

> "Dangling else" is the problem when processing nested if when there are more "if"s than "else"s. In C++, an "if" is always paired with an "else".
