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

- Use range `for` (`:`) to loop through each character (i.e., `for (declaration : expression) statement;`)
- Can also use subscript (`[]`) to access characters (i.e,, `string s("Hello"); std::cout << s[0];`)

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

### Exercise 3.6

Use a range for to change all the characters in a string to X.

```c
std::string s = "abcd efg123";
for (auto &x: s) x = 'X';
```

### Exercise 3.7

What would happen if you define the loop control variable in the previous exercise as type char? Predict the results and then change your program to use a char to see if you were right.

> The string would remain the same as with `char`, we just use a copy of each character in the string. To mutate each character in the string, we must use a reference (`char&`)

```c
std::string s = "abcd efg123";
for (char x: s) x = 'X';
```

### Exercise 3.8

Rewrite the program in the first exercise, first using a while and again using a traditional for loop. Which of the three approaches do you prefer and why?

```c
// while loop
decltype(s.size()) i = 0;
while (i < s.size()) s[i++] = 'X';
```

```c
// for loop
for (unsigned i = 0; i < s.size(); ++i) s[i] = 'X';
```

> I prefer the range for, first approach, because I don't need to create another variable for index (`i`) and I don't need a condition for checking the bound. The range for is the shortest and most direct way to access and mutate each character in the string.

### Exercise 3.9

What does the following program do? Is it valid? If not, why not?

string s;

cout << s[0] << endl;

> The code tries to print the first element in `s`. This is invalid because s is empty so `s[0]` is out of bound.

### Exercise 3.10

Write a program that reads a string of characters including punctuation and writes what was read but with the punctuation removed.

```c
int main() {
	string result, input;
	getline(cin, input);
	for (auto &c: input) {
		if (!ispunct(c)) result.push_back(c);
	}
	cout << result << '\n';
	return 0;
}
```

### Exercise 3.11

Is the following range for legal? If so, what is the type of c?

const string s = "Keep out!";

for (auto \&c : s) { /* ...  \*/ }

> Depending on the loop body. If it tries to mutate `c` (for example, `c = 'C';`) then illegal. Otherwise, legal. `c` is `const char&`.
