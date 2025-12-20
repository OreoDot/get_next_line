*This project has been created as part of the 42 curriculum by dolaniya.*

# get_next_line

## Description

**get_next_line** is a project that consists of implementing a function capable of reading and returning a file’s content **one line at a time**.  
Each call to the function returns the next available line from a given file descriptor, until the end of the file is reached.

The main goal of this project is to understand how to:
- Read data incrementally from a file descriptor
- Manage memory efficiently
- Preserve state between multiple function calls
- Handle variable buffer sizes and incomplete reads

This project introduces persistent memory handling and simulates how real-world programs process input streams line by line.

---

## Instructions

### Compilation

The project is written in **C** and must be compiled with the required flags:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
```

The macro BUFFER_SIZE must be defined at compilation time:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

### Usage

The function prototype is:

```c
char *get_next_line(int fd);
```

- `fd` is a valid file descriptor

Each call returns:

- The next line from the file (including `\n` if present)
- `NULL` when no more lines are available or an error occurs

The function can be used to read:

- Files
- Standard input
- Pipes or redirected input

---

## Algorithm Explanation and Justification

### Overview

The algorithm is designed to read from a file descriptor in small chunks and assemble complete lines before returning them. Because the system does not guarantee that a full line will be read in one operation, the function must carefully store and reuse partial data.

### Core Idea

1. **Read data using a fixed buffer size**
   - Data is read in chunks defined by `BUFFER_SIZE`
   - These chunks may contain:
     - Part of a line
     - A full line
     - Multiple lines

2. **Store unfinished data**
   - If a newline character (`\n`) is not found, the data is saved
   - This saved data persists between function calls using static storage

3. **Detect line boundaries**
   - When a newline is encountered, the function:
     - Extracts the line up to and including `\n`
     - Saves any remaining data for the next call

4. **Return exactly one line per call**
   - Even if multiple lines are read at once, only one line is returned
   - Remaining data is preserved for future calls

5. **Handle end-of-file**
   - If the end of the file is reached:
     - Any remaining data is returned as the last line
     - Subsequent calls return `NULL`

### Justification

This approach is necessary because:

- Files can be very large and cannot always be read entirely into memory
- Input streams may be slow or infinite (e.g., standard input)
- Lines may be split across multiple reads

Using static memory ensures that no data is lost between calls and allows the function to behave like a continuous stream reader.

---

## Resources

### Technical References

- Linux manual pages: `man read`, `man open`, `man close`
- GNU C Library documentation
- 42 documentation on file descriptors and memory management
- Articles on buffered input and stream processing in C

### AI Usage Disclosure

AI tools were used during the learning and documentation phase of this project to:

- Clarify the conceptual behavior of the `get_next_line` function
- Understand buffer-based reading and persistent memory
- Help structure and write this README file

All code implementation decisions, logic, and final validation are performed by me, the Author.