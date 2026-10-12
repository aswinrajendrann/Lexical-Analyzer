# C Lexical Analyzer

A **Lexical Analyzer implemented in C** that reads a C source file, identifies lexemes, and classifies them into token categories. This project demonstrates the fundamental concepts of lexical analysis, file handling, and modular programming in C.

## Overview

Lexical analysis is the first phase of a compiler. It reads source code character by character, groups characters into meaningful units called *lexemes*, and classifies them into tokens.

This project implements a basic lexical analyzer that processes a C source file and displays the identified tokens along with their categories and line numbers.

## Features

* **Keyword recognition** – Identifies supported C keywords.
* **Identifier recognition** – Recognizes variable and function names.
* **Numeric constants** – Handles supported integer, floating-point, exponent, and hexadecimal constants.
* **Operator recognition** – Identifies single-character and multi-character operators.
* **Special character recognition** – Detects symbols such as braces, brackets, parentheses, commas, and semicolons.
* **String and character literals** – Processes supported escape sequences and detects certain malformed literals.
* **Comment handling** – Handles single-line and multi-line comments.
* **Preprocessor directives** – Recognizes directives such as `#include` and `#define`.
* **Line number tracking** – Reports the source line associated with each token.
* **Invalid token detection** – Identifies certain malformed or unsupported token patterns.

## Project Structure

| File       | Description                                        |
| ---------- | -------------------------------------------------- |
| `main.c`   | Entry point of the program                         |
| `file.c`   | Implements source-file handling                    |
| `file.h`   | File-handling declarations                         |
| `lexer.c`  | Performs lexical analysis and token classification |
| `lexer.h`  | Lexer declarations                                 |
| `token.c`  | Token-related implementation                       |
| `token.h`  | Token definitions and declarations                 |
| `sample.c` | Sample C source file used for testing              |

## Requirements

* GCC compiler
* Linux environment or WSL (Windows Subsystem for Linux)

## Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/aswinrajendrann/Lexical-Analyzer.git
cd Lexical-Analyzer
```

### 2. Compile the project

```bash
gcc main.c file.c lexer.c token.c -o lexer
```

### 3. Run the program

```bash
./lexer
```

The program processes the source file configured in `main.c`. By default, it uses `sample.c`. To analyze a different file, update the filename passed to the file-opening function in `main.c`.

## Sample Input

Example C source code from `sample.c`:

```c
#include <stdio.h>

#define MAX 10

int main()
{
    int a = 10;

    if (a >= MAX)
    {
        printf("Hello World");
    }

    return 0;
}
```

## Sample Output

The lexer identifies tokens and displays their categories and source line numbers. A simplified example of the output is:

```text
#include    PREPROCESSOR DIRECTORY    1
<           OPERATOR                  1
stdio       IDENTIFIER                1
.           OPERATOR                  1
h           IDENTIFIER                1
>           OPERATOR                  1
int         KEYWORD                   5
main        IDENTIFIER                5
(           SPECIAL CHARACTER         5
)           SPECIAL CHARACTER         5
{           SPECIAL CHARACTER         6
int         KEYWORD                   7
a           IDENTIFIER                7
=           OPERATOR                  7
10          CONSTANT                  7
;           SPECIAL CHARACTER         7
```

*Note: This is an illustrative excerpt. Exact token names, formatting, and output depend on the implementation.*

## Concepts Practiced

* File handling in C
* Character-by-character input processing
* String manipulation and comparison
* Arrays and structures
* Token classification
* Header files and modular programming
* Basic compiler design concepts

## Scope and Limitations

This project focuses on core lexical analysis and is **not a complete C compiler**. It does not perform syntax analysis, semantic analysis, or code generation. Its recognition rules cover a subset of C syntax, so some advanced language constructs and preprocessor behaviors may not be fully supported.

## Author

**Aswin Rajendran**

GitHub: [@aswinrajendrann](https://github.com/aswinrajendrann)
