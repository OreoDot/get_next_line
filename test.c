#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

// "I am a superhuman"

#define BUFFER_SIZE 9

int main(void)
{
    int open_book;
    int read_book;
    char buffer[BUFFER_SIZE + 1];

    open_book = open("file.txt", O_RDONLY);
    if(open_book < 0)
        return (1);

    // read_book = read(open_book, buffer, BUFFER_SIZE);
    // buffer[read_book] = '\0';

    // printf("the no of bytes %d\n [%s]\n", read_book, buffer);

    while((read_book = read(open_book, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[read_book] = '\0';
        printf("%d\n [%s]\n", read_book, buffer);
    }

    close (open_book);
    return (0);
}