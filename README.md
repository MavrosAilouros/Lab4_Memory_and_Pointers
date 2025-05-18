# Lab 4 – IE-0117 Open Platform Programming

**Course:** IE-0117 – Open Platform Programming  
**Institution:** Universidad de Costa Rica  
**Semester:** I-2025

## Lab Overview

This repository contains the solutions to Lab 4, comprising two programming exercises developed in C:

- **Exercise 1:** Find the longest sequence of consecutive 1s in a dynamically allocated binary matrix, traversed exclusively using pointer arithmetic.
- **Exercise 2:** Identify the longest palindrome word within a given text file, ignoring punctuation and case sensitivity.

Each exercise strictly follows robust programming practices, including dynamic memory management, pointer arithmetic, POSIX compliance, and detailed documentation.

---

## Compilation

Compile the exercises using GCC with strict compilation flags:

### Exercise 1

```bash
gcc -g -Wall -Wextra -pedantic -std=c11 ejercicio1.c -o ej1
```

### Exercise 2

```bash
gcc -g -Wall -Wextra -pedantic -std=c11 ejercicio2.c -o ej2
```

---

## Execution

Run each executable as follows:

### Exercise 1

Run interactively (you will be prompted for matrix size):
```bash
./ej1
```

Automated run (example matrix size of 6):
```bash
echo 6 | ./ej1
```

### Exercise 2

Ensure that `input.txt` is present in the current directory, then run:
```bash
./ej2
```

---

## Memory Checks with Valgrind

Valgrind was used to ensure there are no memory leaks or errors.

### Exercise 1:
```bash
echo 6 | valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./ej1
```

### Exercise 2:
```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./ej2
```

*Check the `LEAK SUMMARY` section in Valgrind output to confirm absence of memory leaks.*

---

## POSIX Compliance

Exercises comply with POSIX standards to ensure maximum portability and interoperability. POSIX-specific functions (`strdup`) are enabled explicitly in code via:

```c
#define _POSIX_C_SOURCE 200809L
```

For further information on POSIX standards, refer to:
- [The Open Group Base Specifications Issue 7, 2018 edition](https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/)

---

## Best Practices

- All functions contain Doxygen-compatible documentation.
- Strict pointer arithmetic without indexing syntax in matrix operations.
- Robust checks for memory allocation and file handling errors.
- Comprehensive tests and validation through Valgrind to avoid memory-related issues.

---

## Author

- **Jafet Cruz**  
- Universidad de Costa Rica – IE-0117 (2025)
