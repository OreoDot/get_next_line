#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFFER_SIZE 8

int main(void)
{
    int fd;
    char buffer[BUFFER_SIZE + 1]; // a pointer to beggining of the buffer
    int bytes_read;

    fd = open("test.txt", O_RDONLY); //this opens the file to be read (takes 2 arg file name and read type O_RDONLY)
    if (fd < 0)
        return (1); //can test this by deleting the test.txt file and run the command 'echo $?' in terminal.

    // bytes_read = read(fd, buffer, BUFFER_SIZE); //this reads the opened file taking 3 arguments, (the opened file, the buffer memory and , )
    // In read(fd, buffer, BUFFER_SIZE), you're telling the system: "Read up to 8 bytes from file descriptor fd and store them starting at buffer.
    
    //buffer[bytes_read] = '\0'; //this adds a null terminator to the end of the buffer, so it can be formatted as a string, converting the filled 
    //portion of the array into a valid C-style string.

    // printf("Read %d bytes: [%s]\n", bytes_read, buffer);

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        printf("Chunk: [%s]\n", buffer);
    }

    close(fd);
    return (0);

    //printf("Read %d bytes: [%s]\n", bytes_read, buffer);
}

// bytes_read = read(fd, buffer, BUFFER_SIZE); followed by while (bytes_read > 0)
//This reads only once before the loop, storing the result in bytes_read. 
//The while loop then checks if bytes_read > 0, and if true, 
//it executes the body (null-terminates and prints) exactly once—regardless of file size. 
//It doesn't read additional data; after printing the first chunk, the loop exits. 
//This means it only handles the first up to 8 bytes of the file, ignoring the rest. 
//It's essentially a single-read operation with a pointless loop that runs at most once.


// That means you now understand:

// what read() actually does

// how data arrives in chunks, not lines

// why BUFFER_SIZE matters

// and how raw bytes turn into something you can work with

// That’s huge.

// ✅ What this means now
// You’re officially ready for the real part of get_next_line.

// The next step is to build the logic that sits on top of read() — the part that:

// keeps leftover data (the “stash” / cache),

// finds \n,

// returns exactly one line at a time,

// and remembers what’s left for the next call.