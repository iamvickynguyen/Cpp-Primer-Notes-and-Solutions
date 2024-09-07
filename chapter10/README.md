# Chapter 10. Generic Algorithms

- The algorithms doesn't work directly on the container. Instead, they operate by traversing a range of elements between the 2 iterators.

## 10.2. A First Look at the Algorithms

### 10.2.1. Read-Only Algorithms

- It's best to use `cbegin()` and `cend()` with algorithms that read, but do not write.

Example:

```c
string sum = accumulate(v.cbegin(), v.cend(), string(""));

// error: no + on const char*
string sum = accumulate(v.cbegin(), v.cend(), "");
```

### 10.2.2. Algorithms that Write Container Elements

- Algorithms do not check write operations. They assume the destination is large enough to hold the number of elements being written.

Example:

```c
vector<int> vec;

// fill_n(dest, n, val);
fill_n(vec.begin(), vec.end(), 0); // reset all elements to 0

// disaster: attempts to write to 10 (nonexistent) elements in vec
fill_n(vec.begin(), 10, 0);
```

#### `back_inserter`

- *Insert iterator* ensures that an algorithm has enough elements to hold the output.
- `back_inserter` takes a reference to a container and returns an insert iterator bound to that container. When we assign through that iterator, the assignment calls `push_back` to add an element.

Example:

```c
vector<int> vec;
auto it = back_inserter(vec);
*it = 42; // vec has 1 element with value 42
```

- `back_inserter` is used as the destination of an algorithm.

Example:

```c
vector<int> vec;
// ok: back_inserter creates an insert iterator that adds elements to vec
fill_n(back_inserter(vec), 10, 0); // appends 10 elements to vec
```

### 10.2.3. Algorithms that Reorder Container Elements

- Note that the library algorithms operate on iterators, not containers. Thus, they cannot (directly) add or remove elements.

Example:

```c
// sort words
sort(words.begin(), words.end());

// unique reorders the input range so that each word appears once in the
// front portion of the range and returns an iterator one past the unique range.
auto end_unique = unique(words.begin(), words.end());

// erase uses a vector operation to remove the nonunique elements
words.erase(end_unique, words.end());

/*
fox | jumps | over | quick | red | red | the | slow | the | turtle

becomes

fox | jumps | over | quick | red | slow | the | turtle | ?? | ??
    |       |      |       |     |      |     |        | ^
    |       |      |       |     |      |     |        | end_unique
*/
```
