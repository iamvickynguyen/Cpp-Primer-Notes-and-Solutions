# Chapter 9. Sequential Containers

<!-- vim-markdown-toc GFM -->

* [9.1. Overview of the Sequential Containers](#91-overview-of-the-sequential-containers)

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

