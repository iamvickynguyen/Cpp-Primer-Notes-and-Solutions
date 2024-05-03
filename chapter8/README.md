# Chapter 8. The IO Library

<!-- vim-markdown-toc GFM -->

* [8.1.3 Managing the Output Buffer](#813-managing-the-output-buffer)

<!-- vim-markdown-toc -->

- `istream`, `ostream`, `cin`, `cout`, `cerr`, `>>`, `<<`, `getline`, etc.
- `iostream`: handle IO to console
- `fstream`: handle IO to named files
- `stringstream`: do IO to in-memory `string`s

### 8.1.3 Managing the Output Buffer

- Several conditions that cause the buffer to be flushed (written) to the actual output device or file:
    - The program completes normally.
    - When the buffer is full. It will be flushed before writing the next value.
    - Manually use a manipulator such as `endl`.
    - Use `unitbuf`. By default, `unitbuf` is set for `cerr`.
    - The output stream is flushed when the input stream, to which it is tied, is read or written (i.e., `cin`, `cerr` are tied to `cout`).
- **Caution**: output buffers are not flushed when the program terminates abnormally.
