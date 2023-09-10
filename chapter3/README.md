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

## 3.5. Arrays

- Array is like `vector` but fixed size

### 3.5.1. Defining and Initializing Built-in Arrays

- Array is a compound type, form `a[d]`, where `a` is name, `d` is dimension
- Dimension must be known at compile time

Examples:

```c
unsigned cnt = 42; // not a constant expression
constexpr unsigned sz = 42; // constant expression
                            // constexpr see § 2.4.4 (p. 66)
int arr[10]; // array of ten ints
int *parr[sz]; // array of 42 pointers to int
string bad[cnt]; // error: cnt is not a constant expression
string strs[get_size()]; // ok if get_size is constexpr, error otherwise
```

- We can list initialize an array, then we are allowed to omit the dimension

Examples:

```c
const unsigned sz = 3;
int ia1[sz] = {0,1,2}; // array of three ints with values 0, 1, 2
int a2[] = {0, 1, 2}; // an array of dimension 3
int a3[5] = {0, 1, 2}; // equivalent to a3[] = {0, 1, 2, 0, 0}
string a4[3] = {"hi", "bye"}; // same as a4[] = {"hi", "bye", ""}
int a5[2] = {0,1,2}; // error: too many initializers
```

- Character arrays are special

Examples:

```c
char a1[] = {'C', '+', '+'}; // list initialization, no null
char a2[] = {'C', '+', '+', '\0'}; // list initialization, explicit null
char a3[] = "C++"; // null terminator added automatically
const char a4[6] = "Daniel"; // error: no space for the null!
```

- For standard features, we cannot copy or do assignment with arrays

Examples:

```c
int a[] = {0, 1, 2}; // array of three ints
int a2[] = a; // error: cannot initialize one array with another
a2 = a; // error: cannot assign one array to another
```

- To read complicated array declarations, start with the name, then read from inside out

Example:

```c
int *(&arry)[10] = ptrs; // arry is a reference to an array of ten pointers
```

### 3.5.3. Pointers and Arrays

- When we use an array, the compiler ordinarily converts the array to a pointer. Specifically, it will substitute a pointer to the first element

Example:

```c
string nums[] = {"one", "two", "three"}; // array of strings
string *p = &nums[0]; // p points to the first element in nums
string *p2 = nums; // equivalent to p2 = &nums[0]
```

- `auto` deduced type is a pointer, not an array

Example:

```c
int ia[] = {0,1,2,3,4,5,6,7,8,9}; // ia is an array of ten ints
auto ia2(ia); // ia2 is an int* that points to the first element in ia
ia2 = 42; // error: ia2 is a pointer, and we can't assign an int to a pointer
```

- `decltype` returns an array

Example:

```c
// ia3 is an array of ten ints
decltype(ia) ia3 = {0,1,2,3,4,5,6,7,8,9};
ia3 = p; // error: can't assign an int* to an array
ia3[4] = i; // ok: assigns the value of i to an element in ia3
```

- Pointers have same operators as iterators

Example:

```c
int arr[] = {0,1,2,3,4,5,6,7,8,9};
int *p = arr; // p points to the first element in arr
++p; // p points to arr[1]
```

- Can use standard library to get begin and end pointers

Example:

```c
int ia[] = {0,1,2,3,4,5,6,7,8,9}; // ia is an array of ten ints
int *beg = begin(ia); // pointer to the first element in ia
int *last = end(ia); // pointer one past the last element in ia
```

- Pointer arithmetic: increment, comparisons, addition of an integral value, subtraction of 2 pointers

Examples:

```c
constexpr size_t sz = 5;
int arr[sz] = {1,2,3,4,5};
int *ip = arr; // equivalent to int *ip = &arr[0]
int *ip2 = ip + 4; // ip2 points to arr[4], the last element in arr
```

```c
// ok: arr is converted to a pointer to its first element; p points one past the end of arr
int *p = arr + sz; // use caution -- do not dereference!
int *p2 = arr + 10; // error: arr has only 5 elements; p2 has undefined value
```

```c
auto n = end(arr) - begin(arr); // n is 5, the number of elements in arr
```

```c
int *b = arr, *e = arr + sz;
while (b < e) {
    // use *b
    ++b;
}
```

- Can use subscript operator on any pointer, as long as it points to an element
- Unlike subscripts for vector and string, the index of the built-in subscript operator is not an unsigned type.

Example:

```c
int ia[] = {0,2,4,6,8}; // array with 5 elements of type int
int *p = &ia[2]; // p points to the element indexed by 2
int j = p[1]; // p[1] is equivalent to *(p + 1),
              // p[1] is the same element as ia[3]
int k = p[-2]; // p[-2] is the same element as ia[0]
```

### 3.5.4. C-Style Character Strings

- C++ supports C-style strings, but they should be avoided because C-style strings are rich source of bugs and are the root cause of many security problems
- Use standard string library rather than C-style strings
- C-style strings are not a type, but a convention of representing and using character strings
- Strings are character arrays and are null terminated

Example:

```c
char ca[] = {'C', '+', '+'}; // not null terminated
cout << strlen(ca) << endl; // disaster: ca isn't null terminated, result is undefined
```

### 3.5.5. Interfacing to Older Code

- Initialize a character pointer from a string with `c_str`

Example:

```c
string s("Hello World"); // s holds Hello World
char *str = s; // error: can't initialize a char* from a string
const char *str = s.c_str(); // ok
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

### Exercise 3.27

Assuming txt\_size is a function that takes no arguments and returns an int value, which of the following definitions are illegal? Explain why. unsigned buf\_size = 1024;

```c
(a) int ia[buf_size]; // illegal, buf_size is not constexpr
(b) int ia[4 * 7 - 14]; // legal
(c) int ia[txt_size()]; // illegal, return value is not constexpr 
(d) char st[11] = "fundamental"; // illegal, no space for null character
```

### Exercise 3.28

What are the values in the following arrays?

string sa[10];

int ia[10];

int main() {

 string sa2[10]; int ia2[10];

}

```
sa: ""
ia: 0
sa2: ""
ia2: undefined
```

### Exercise 3.29

List some of the drawbacks of using an array instead of a vector.

> Size must be known at compile time, no APIs like vector

### Exercise 3.30

Identify the indexing errors in the following code

```c
constexpr size_t array_size = 10;
int ia[array_size];
for (size_t ix = 1; ix <= array_size; ++ix) // error, fix: for (size_t ix = 0 ix < array_size; ++ix)
    ia[ix] = ix;
```

### Exercise 3.32

Copy the array you defined in the previous exercise into another array. Rewrite your program to use vectors.

[Code](e3_32.cpp)

### Exercise 3.33

What would happen if we did not initialize the scores array in the program on page 116?

> Values are undefined

### Exercise 3.34

Given that p1 and p2 point to elements in the same array, what does the following code do? Are there values of p1 or p2 that make this code illegal?

p1 += p2 - p1;

> Legal, this code increment the pointer p1 to the offset (p2 - p1). In the end, p1 and p2 point to the same element

### Exercise 3.35

Using pointers, write a program to set the elements in an array to zero.

```c
int arr[] = {1, 2, 3, 4, 5};
for (int *p = arr; p != arr + 5; ++p) *p = 0;
```

### Exercise 3.36

Write a program to compare two arrays for equality. Write a similar program to compare two vectors.

[Code](e3_36.cpp)

### Exercise 3.37

What does the following program do?

```c
const char ca[] = {'h', 'e', 'l', 'l', 'o'};
const char *cp = ca;
while (*cp) {
    cout << *cp << endl; ++cp;
}
```

> It tries to print each character in `ca`. However, since there is no null terminated character at the end, the result will be undefined. Most of the time, the loop won't terminate and the program will print garbage 

### Exercise 3.38

In this section, we noted that it was not only illegal but meaningless to try to add two pointers. Why would adding two pointers be meaningless?

> Pointers contain addresses. Adding 2 pointers makes no sense. [See stackoverflow](https://stackoverflow.com/a/25667730) 

### Exercise 3.39

Write a program to compare two strings. Now write a program to compare the values of two C-style character strings.

[Code](e3_39.cpp)

### Exercise 3.40

Write a program to define two character arrays initialized from string literals. Now define a third character array to hold the concatenation of the two arrays. Use strcpy and strcat to copy the two arrays into the third.

[Code](e3_40.cpp)

### Exercise 3.41

Write a program to initialize a vector from an array of ints.

```c
int arr[] = {1, 2, 3};
vector<int> vec(begin(arr), end(arr));
```

### Exercise 3.42

Write a program to copy a vector of ints into an array of ints.

```c
vector<int> vec = {1, 2, 3};
int arr[3];
for (int i = 0; i < 3; ++i) arr[i] = vec[i];
```
