# Chapter 9. Sequential Containers

<!-- vim-markdown-toc GFM -->

* [9.1. Overview of the Sequential Containers](#91-overview-of-the-sequential-containers)
* [9.2. Container Library Overview](#92-container-library-overview)
    * [9.2.1. Iterators](#921-iterators)
    * [9.2.2. Container Type Members](#922-container-type-members)
    * [9.2.4. Defining and Initializing a Container](#924-defining-and-initializing-a-container)
    * [9.2.5. Assignment and `swap`](#925-assignment-and-swap)
* [9.3. Sequential Container Operations](#93-sequential-container-operations)
    * [9.3.1 Adding Elements to a Sequential Container](#931-adding-elements-to-a-sequential-container)
* [9.6. Container Adaptors](#96-container-adaptors)
* [Exercises](#exercises)
    * [Exercise 9.12:](#exercise-912)

<!-- vim-markdown-toc -->

- A *container* holds a collection of objects of a specific type.
- The *sequential containers* let the programmer control the order in which the elements are stored and accessed.

## 9.1. Overview of the Sequential Containers

- Trade-offs:
    - The costs to add or delete elements
    - The costs to perform nonsequential access to elements


| Containers | Notes |
|----------|----------|
|   `vector`   | - Flexible size. Fast random access.</br>- Insert and delete item other than at the back is slow. |
|   `deque`   | - Double-ended queue. Fast random access.</br>- Fast delete/insert at front or back |
| `list` | - Doubly linked list. Only bidirectional sequential access.</br>- Fast insert/delete at any point. |
| `forward_list` | - Singly linked list. Only sequential access in 1 direction.</br>- Fast insert/delete at any point. |
| `array` | - Fixed size. Fast random access.</br>- Cannot add/remove item. |
| `string` | - Specialized container, similar to `vector`, only contain characters.</br>- Fast random access.</br>- Fast insert/delete at the back. |

- [More about C++ containers](https://en.cppreference.com/w/cpp/container)
- **Tip**: Use `vector`, unless there is a good reason to use another container.

## 9.2. Container Library Overview

### 9.2.1. Iterators

- 2 iterators, `begin` and `end`, form an *iterator range*, if:
    - They refer to elements of, or 1 past the end of, the same container
    - Reach `end` by incrementing `begin`. `end` must not precede `begin`

### 9.2.2. Container Type Members

- To use the types, we must name the class.

Example:

```c
list<string>::iterator iter;
vector<int>::difference_type count;
```

- Best practices: When write access is not needed, use `cbegin` and `cend`.

### 9.2.4. Defining and Initializing a Container

- When initializing a container as a copy of another container, the container type and element type of both containers must be identical.

Example:

```c
list<string> authors = { "Milton", "Shakespeare", "Austen" };
vector<const char*> articles = { "a", "an", "the" };

list<string> list2(authors); // ok: types match
deque<string> authList(authors); // error: container types don't match
vector<string> words(articles); // error: element types must match
// ok: converts const char* elements to string
forward_list<string> words(articles.begin(), articles.end());
```

- We can use iterators to copy a subsequence of a container.

Example:

```c
// it is an iterator denoting an element in authors
// copies up to but not including the element denoted by it
deque<string> authList(authors.begin(), it);
```

- `array`s have fixed size, so we need to specify the element type and the container size.

Example:

```c
array<int, 42> // type is: array the holds 42 ints
array<int, 42>::size_type i; // array type includes element type and size
array<int>::size_type j; // error: array<int> is not a type
```

### 9.2.5. Assignment and `swap`

- Unlike built-in `array`, the library `array` type allows assignment when the left-hand and right-hand operands have the same type.

Example:

```c
array<int, 10> a1 = {0, 1, 2};
array<int, 10> a2 = {0}; // all elements are 0
a1 = a2; // replaces elements in a1
a2 = {0}; // error: cannot assign to an array from a braced list
// The right-hand operand might have different size from the left-hand operand, the array type doesn't support
// assign and doesn't allow assignment from a braced list of values.
```

- Using assign for sequential containers only

Example:

```c
list<string> names;
vector<const char*> oldstyle;
names = oldstyle; // error: container types don't match
// ok: can convert from const char* to string
names.assign(oldstyle.cbegin(), oldstyle.cend());
```

```c
// equivalent to slist1.clear()
// followed by slist1.insert(slist1.begin(), 10, "Hiya!");
list<string> slist1(1); // one element, which is the empty string
slist1.assign(10, "Hiya!"); // ten elements, each on is Hiya!
```

- Excepting `array`, `swap` doesn't copy, delete, or insert any elements and is guaranteed to run in constant time.
- When swapping 2 containers, the elements themselves aren't swapped, but the internal data structures are swapped.

Example:

```c
vector<string> svec1(10); // vector with 10 elements
vector<string> svec2(24); // vector with 24 elements
swap(svec1, svec2);
```

## 9.3. Sequential Container Operations

### 9.3.1 Adding Elements to a Sequential Container

- `push_back`, `push_front`, `emplace_back`, `emplace_front`, `insert`, `emplace`
- `emplace` functions construct elements in the container. The arguments to these functions must match a constructor for the element type.

```c
c.emplace_back("123-456", 25, 15.99);

// error: no version of push_back that takes 3 arguments
c.push_back("123-456", 25, 15.99);

// ok: create a temporary Sales_data object to pass to push_back
c.push_back(Sales_data("123-456", 25, 15.99));
```

## 9.6. Container Adaptors

- A container adaptor takes an existing container type and makes it act like a different type.
- Each adaptor defines 2 constructors: the default constructor that creates an empty object, and a constructor that takes a containers and initializes the adaptor by copying the given container.
Example:

```c
stack<int> stk(deq); // copies elements from deq into stk

// empty stack implemented on top of vector
stack<string, vector<string>> str_stk;

// str_stk2 is implemented on top of vector and initially holds a copy of svec
stack<string, vector<string>> str_stk2(svec);
``` 

## Exercises

### Exercise 9.12:

Explain the differences between the constructor that takes a container to copy and the constructor that takes two iterators.

> The constructor that takes a container to copy assumes the container type and element type of both containers must be identical.

> The constructor that takes 2 iterators to copy doesn't require the container type and element type of both containers to be identical. As long as the element type can be converted.

