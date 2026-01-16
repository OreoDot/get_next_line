*This project has been created as part of the 42 curriculum by dolaniya.*

# get_next_line

## Description

**get_next_line** is a project that consists of implementing a function capable of reading and returning a file's content **one line at a time**.  
Each call to the function returns the next available line from a given file descriptor, until the end of the file is reached.

The main goal of this project is to understand how to:
- Read data incrementally from a file descriptor
- Manage memory efficiently
- Preserve state between multiple function calls
- Handle variable buffer sizes and incomplete reads
- Manage multiple file descriptors simultaneously (bonus)

This project introduces persistent memory handling and simulates how real-world programs process input streams line by line.

---

## Instructions

### Compilation

The project is written in **C** and must be compiled with the required flags:

#### Mandatory

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

#### Bonus

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c
```

The macro `BUFFER_SIZE` must be defined at compilation time and determines how many bytes are read per `read()` call.

### Usage

The function prototype is:

```c
char *get_next_line(int fd);
```

**Parameters:**
- `fd` - A valid file descriptor

**Return values:**
- The next line from the file (including `\n` if present)
- `NULL` when no more lines are available or an error occurs

**The function can be used to read:**
- Regular files
- Standard input (stdin, fd = 0)
- Pipes or redirected input
- Multiple file descriptors simultaneously (bonus only)

---

## Mandatory vs Bonus

### Mandatory Part

**File structure:**
```
get_next_line.c
get_next_line_utils.c
get_next_line.h
```

**Features:**
- ✅ Reads one line at a time from a **single** file descriptor
- ✅ Uses a **static buffer** to preserve leftover data between calls
- ✅ Handles files with or without final newline
- ✅ Memory-safe (no leaks)

**Implementation:**

```c
char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];  // Single static buffer
    // ... reads from one fd at a time
}
```

**Key characteristic:** Can only read from **one file descriptor at a time**. If you switch to a different `fd`, the previous one's state is lost.

**Example:**

```c
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);

char *line1 = get_next_line(fd1);  // Reads line 1 from file1
char *line2 = get_next_line(fd2);  // ❌ Loses file1's state!
char *line3 = get_next_line(fd1);  // ❌ Restarts from beginning (data lost)
```

---

### Bonus Part

**File structure:**
```
get_next_line_bonus.c
get_next_line_utils_bonus.c
get_next_line_bonus.h
```

**Features:**
- ✅ All mandatory features
- ✅ **Manages multiple file descriptors simultaneously**
- ✅ Each `fd` has its own independent buffer
- ✅ Can switch between files without losing state

**Implementation:**

```c
#define MAX_BUFFER 1024

char *get_next_line(int fd)
{
    static char buffer[MAX_BUFFER][BUFFER_SIZE + 1];  // Array of buffers
    // ... buffer[fd] stores leftover data for each fd
}
```

**Key characteristic:** Uses a **2D static array** where each file descriptor gets its own buffer slot.

**Example:**

```c
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);
int fd3 = open("file3.txt", O_RDONLY);

char *line1 = get_next_line(fd1);  // "Line 1 from file1\n"
char *line2 = get_next_line(fd2);  // "Line 1 from file2\n"
char *line3 = get_next_line(fd3);  // "Line 1 from file3\n"

char *line4 = get_next_line(fd1);  // ✅ "Line 2 from file1\n" (state preserved!)
char *line5 = get_next_line(fd2);  // ✅ "Line 2 from file2\n"
```

**Memory layout:**

```
buffer[0]:  [leftover data from fd 0 (stdin)]
buffer[1]:  [leftover data from fd 1]
buffer[2]:  [leftover data from fd 2]
buffer[3]:  [leftover data from fd 3]
...
buffer[1023]: [leftover data from fd 1023]
```

---

## Algorithm Explanation and Justification

### Overview

The algorithm is designed to read from a file descriptor in small chunks and assemble complete lines before returning them. Because the system does not guarantee that a full line will be read in one operation, the function must carefully store and reuse partial data.

### Core Idea

#### 1. **Read data using a fixed buffer size**

- Data is read in chunks defined by `BUFFER_SIZE`
- These chunks may contain:
  - Part of a line
  - A full line
  - Multiple lines

#### 2. **Store unfinished data**

- **Mandatory:** Uses a single static buffer
  ```c
  static char buffer[BUFFER_SIZE + 1];
  ```
- **Bonus:** Uses an array of static buffers (one per fd)
  ```c
  static char buffer[MAX_BUFFER][BUFFER_SIZE + 1];
  ```
- If a newline character (`\n`) is not found, the data is saved
- This saved data persists between function calls using static storage

#### 3. **Detect line boundaries**

When a newline is encountered, the function:
1. Extracts the line up to and including `\n`
2. Saves any remaining data for the next call
3. Uses `ft_memmove` to shift leftover data to the beginning of the buffer

**Example:**

```
Buffer contains: "Hello\nWorld\n"
                      ↑
              First newline found

Step 1: Extract "Hello\n"
Step 2: Shift buffer left
Buffer now: "World\n"
```

#### 4. **Return exactly one line per call**

- Even if multiple lines are read at once, only one line is returned
- Remaining data is preserved for future calls
- This happens in the `extract_line()` function:

```c
static char *extract_line(char *buffer, char *ini_line)
{
    char *find_newline;
    char *final_line;
    char *str_nl;

    find_newline = ft_strchr(buffer, '\n');        // Find '\n'
    str_nl = ft_substr(buffer, 0, (find_newline - buffer) + 1);  // Extract line
    final_line = ft_strjoin(ini_line, str_nl);     // Join with accumulated data
    free(ini_line);
    free(str_nl);
    ft_memmove(buffer, find_newline + 1, ...);     // Shift leftover data
    return (final_line);
}
```

#### 5. **Handle end-of-file**

If the end of the file is reached:
- Any remaining data (without `\n`) is returned as the last line
- Subsequent calls return `NULL`
- The buffer is cleared for reuse

---

### Justification

This approach is necessary because:

- **Files can be very large** and cannot always be read entirely into memory
- **Input streams may be slow or infinite** (e.g., standard input, network sockets)
- **Lines may be split across multiple reads** (if line length > BUFFER_SIZE)
- **Multiple file descriptors require independent state** (bonus)

Using static memory ensures that:
- ✅ No data is lost between calls
- ✅ The function behaves like a continuous stream reader
- ✅ Each file descriptor maintains its own state (bonus)
- ✅ No memory leaks occur (leftover data stored in static array, not heap)

---

## Key Differences: Mandatory vs Bonus

| Feature | Mandatory | Bonus |
|---------|-----------|-------|
| **File descriptors** | Single fd at a time | Multiple fds simultaneously |
| **Static storage** | `buffer[BUFFER_SIZE + 1]` | `buffer[MAX_BUFFER][BUFFER_SIZE + 1]` |
| **Memory usage** | ~43 bytes (1 buffer) | ~43 KB (1024 buffers) |
| **State preservation** | Lost when switching fds | Preserved for each fd |
| **Complexity** | Simple | Moderate |
| **Use case** | Reading one file sequentially | Reading multiple files interleaved |

---

## Memory Management

### Static vs Dynamic Allocation

**Why use static arrays instead of malloc?**

#### Mandatory:
```c
static char buffer[BUFFER_SIZE + 1];  // Lives in DATA segment
```

**Benefits:**
- ✅ No need to `free()` (automatically managed by OS)
- ✅ No memory leaks when function exits early
- ✅ Persists across function calls
- ✅ Fast (no heap allocation overhead)

#### Bonus:
```c
static char buffer[MAX_BUFFER][BUFFER_SIZE + 1];  // 2D array in DATA segment
```

**Benefits:**
- ✅ Same as mandatory
- ✅ Each fd gets independent storage
- ✅ No memory leaks even if some fds are not read to EOF

**Trade-off:**
- ⚠️ Memory usage: `MAX_BUFFER × (BUFFER_SIZE + 1)` bytes
- ⚠️ Limited to `MAX_BUFFER` simultaneous file descriptors (typically 1024)

---

## Testing

### Test with different BUFFER_SIZE values:

```bash
# Small buffer (forces multiple reads)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c

# Medium buffer
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c

# Large buffer (may read entire file at once)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=10000 get_next_line.c get_next_line_utils.c
```

### Memory leak testing:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./test_program
```

**Expected output:**
```
All heap blocks were freed -- no leaks are possible
```

### Bonus testing (multiple fds):

```c
int main(void)
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line;

    // Read interleaved
    line = get_next_line(fd1); printf("[fd1] %s", line); free(line);
    line = get_next_line(fd2); printf("[fd2] %s", line); free(line);
    line = get_next_line(fd1); printf("[fd1] %s", line); free(line);
    line = get_next_line(fd2); printf("[fd2] %s", line); free(line);

    close(fd1);
    close(fd2);
    return (0);
}
```

---

## Resources

- https://www.tutorialspoint.com/cprogramming/c_static_variables.htm
- https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/#:~:text=to%20the%20file.-,Reading%20from%20a%20File%20Descriptor%20in%20C,void%20*buf%2C%20size_t%20count)%3B


### Technical References

- Linux manual pages: `man 2 read`, `man 2 open`, `man 2 close`
- GNU C Library documentation
- 42 documentation on file descriptors and memory management
- Articles on buffered input and stream processing in C
- Static storage duration in C

### AI Usage Disclosure

AI tools were used during the learning and documentation phase of this project to:

- Clarify the conceptual behavior of the `get_next_line` function
- Understand buffer-based reading and persistent memory
- Explain the difference between single-fd and multi-fd implementations
- Help structure and write this README file
- Debug memory management issues and optimize the algorithm

All code implementation decisions, logic, testing, and final validation are performed by me, the author (dolaniya).

---

## License

This project is part of the 42 curriculum and follows 42's academic policies.