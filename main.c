#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFFER_SIZE 4

int main(void)
{
    int fd;
    char buffer[BUFFER_SIZE + 1];
    int bytes_read;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);

    bytes_read = read(fd, buffer, BUFFER_SIZE);
    buffer[bytes_read] = '\0';

    printf("Read %d bytes: [%s]\n", bytes_read, buffer);

    // while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    // {
    //     buffer[bytes_read] = '\0';
    //     printf("Chunk: [%s]\n", buffer);
    // }

    close(fd);
    return (0);
}
