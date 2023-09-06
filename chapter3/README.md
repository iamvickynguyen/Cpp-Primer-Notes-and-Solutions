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

## 3.3. Library `vector` Type

- `vector` is somtimes called `container`
- *Templates* are instructions to the compiler for generating classes or functions

> "Templates are cookie cutters, not cookies themselves." - Michael D. Adams, Professor at University of Victoria

- *Instantiation*: create classes or functions from templates
- `vector` is a template, not a type. Types generated from vector must include the element type (i.e., `vector<int>`)

### 3.3.1. Defining and Initializing `vectors`

- List initializing a `vector`:

Examples

```c
vector<string> articles = {"a", "an", "the"};
vector<string> v1{"a", "an", "the"};
```

- To use `size_type`, we must name the type (i.e., `vector<int>::size_type`)

## 3.4. Introducing Iterators

- All of the library containers have iterators, but only a few of them support the subscript operator
- The iterator returned by `end()` is off-the-end iterator
- We have `iterator` and `const_iterator`

Examples

```c
vector<int>::iterator it; // it can read and write vector<int> elements
string::iterator it2; // it2 can read and write characters in a string
vector<int>::const_iterator it3; // it3 can read but not write elements
string::const_iterator it4; // it4 can read but not write characters
```

```c
vector<int> v;
const vector<int> cv;
auto it1 = v.begin(); // it1 has type vector<int>::iterator
auto it2 = cv.begin(); // it2 has type vector<int>::const_iterator
```

```c
auto it3 = v.cbegin(); // it3 has type vector<int>::const_iterator
```

- Parentheses are important in combining dereference and member access

Example:

```c
(*it).empty() // dereferences it and calls the member empty on the resulting object
*it.empty() // error: attempts to fetch the member named empty from it
            // but it is an iterator and has no member named empty
```

- `it->mem` is same as `(*it).mem`

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

### Exercise 3.12

Which, if any, of the following vector definitions are in error? For those that are legal, explain what the definition does. For those that are not legal, explain why they are illegal.

```c
(a) vector<vector<int>> ivec; // legal, create an empty 2d vector of int
(b) vector<string> svec = ivec; // illegal, different type
(c) vector<string> svec(10, "null"); // legal, create a vector of string with 10 items and their values are "null"
```

### Exercise 3.13

How many elements are there in each of the following vectors? What are the values of the elements?

```c
(a) vector<int> v1; // 0 element
(b) vector<int> v2(10); // 10 elements, value is 0
(c) vector<int> v3(10, 42); // 10 elements, value is 42
(d) vector<int> v4{10}; // 1 element, value is 10
(e) vector<int> v5{10, 42}; // 2 elements: 10, 42
(f) vector<string> v6{10}; // 10 elements, value is "" 
(g) vector<string> v7{10, "hi"}; // 10 elements, value is "hi" 
```

### Exercise 3.17

Read a sequence of words from cin and store the values a vector. After you’ve read all the words, process the vector and change each word to uppercase. Print the transformed elements, eight words to a line.

[Code](e3_17.cpp)

### Exercise 3.18

Is the following program legal? If not, how might you fix it?

vector<int> ivec;

ivec[0] = 42;

> Illegal because `ivec` is empty. Fix: `vector<int> ivec{42};` 

### Exercise 3.19

List three ways to define a vector and give it ten elements, each with the value 42. Indicate whether there is a preferred way to do so and why.

```c
vector<int> v1(10, 42);
vector<int> v2{42,42,42,42,42,42,42,42,42,42};
vector<int> v3;
for (int i = 0; i < 10; ++i) v3.push_back(42);
```

> I prefer the first one `v1`

### Exercise 3.20

Read a set of integers into a vector. Print the sum of each pair of adjacent elements. Change your program so that it prints the sum of the first and last elements, followed by the sum of the second and second-tolast, and so on.

[Code part 1](e3_20_1.cpp)

[Code part 2](e3_20_2.cpp)

### Exercise 3.22

Revise the loop that printed the first paragraph in text to instead change the elements in text that correspond to the first paragraph to all uppercase. After you’ve updated text, print its contents.

[Code](e3_22.cpp)

### Exercise 3.23

Write a program to create a vector with ten int elements. Using an iterator, assign each element a value that is twice its current value. Test your program by printing the vector.

[Code](e3_23.cpp)

### Exercise 3.25

Rewrite the grade clustering program from § 3.3.3 (p. 104) using iterators instead of subscripts.

```c
vector<unsigned> scores(11, 0);
unsigned grade;
while (cin >> grade) {
	if (grade <= 100)
		++*(scores.begin() + grade/10);
}
```

### Exercise 3.26

In the binary search program on page 112, why did we write mid = beg + (end - beg) / 2; instead of mid = (beg + end)/2;?

> There is no `+` operator for 2 iterators
