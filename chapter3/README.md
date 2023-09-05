# Chapter 3. Strings, Vectors, and Arrays

## 3.1. Namespace `using` Declarations

- `::` is scope operator. Left hand side is scope and right hand side is the name (i.e., `std::cin` means using the name `cin` from the namespace `std`)
- `using` declaration lets us access the name directly

Example:

```c
#include <iostream>
using std::cin;

int main() {
    int i;
    cin >> i;       // ok: cin is a synonym for std::cin
    cout << i;      // error: no using declaration; we must use the full name
    std::cout << i; // ok: explicitly use cout from namepsace std
    return 0;
}
```

- Important: Headers should not include `using` declarations

## 3.2. Library `string` Type

- Using `=` means copy initialize
- Without `=` means direct initialize

Example:

```c
string s1;            // default initialization; s1 is the empty string
string s2 = s1;       // s2 is a copy of  s1
string s3 = "hiya";   // s3 is a copy of the string literal
string s4(10, 'c');   // s4 is cccccccccc
```

- `size()` and `length()` are the same member functions
- Instead of using `string::size_type`, can do `auto len = line.size(); // len has type string::size_type`
- Note that `size()` returns an `unsigned` type, so avoid using `int` with `size()`. Mixing `unsigned` and `int` can have surprising results 
- `string` literals are not standard library `string`s
- Adding strings and string or character literals, at least 1 operand to each `+` operator must be of `string` type

Example:

```c
string s4 = s1 + ", ";           // ok: adding a string and a literal
string s5 = "hello" + ", ";      // error: no string operand
string s6 = s1 + ", " + "world"; // ok: each + has a string operand
                                 // same as string s6 = (s1 + ", ") + "world";
string s7 = "hello" + ", " + s2; // error: can't add string literals
```

## Exercises

### Exercise 3.2

Write a program to read the standard input a line at a time. Modify your program to read a word at a time.

```c
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

// read line by line
int main() {
	string line;
	while (getline(cin, line)) cout << line << '\n'; 
	return 0;
}
```

```c
// read word by word
int main() {
	string word;
	while (cin >> word) cout << word << '\n'; 
	return 0;
}
```

### Exercise 3.3

Explain how whitespace characters are handled in the string input operator and in the getline function.

> `getline` ignores whitespaces, it uses newline characters (`\n`) as separators. `getline(a, b, delim)` uses `delim` as separators. `>>` uses whitespaces as separators.

### Exercise 3.5

Write a program to read strings from the standard input, concatenating what is read into one large string. Print the concatenated string. Next, change the program to separate adjacent input strings by a space.

```c
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

int main() {
	string result = "", s;
	while (getline(cin, s)) {
		result.append(s);
	}

	cout << result << '\n';
	return 0;
}
```

```c
int main() {
	string result = "", s;
	cin >> result;
	while (cin >> s) result.append(" " + s);
	cout << result << '\n';
	return 0;
}
```
