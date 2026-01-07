// #ifndef GET_NEXT_LINE_H
// #define GET_NEXT_LINE_H

// #define BUFFER_SIZE 12;

// #include <unistd.h>
// #include <stdlib.h>

// char    *get_next_line(int fd);
// // char    *ft_find_line(int fd, char *buffer);
// // char    *ft_line_generator(char *buffer, char *temp);
// // size_t  ft_charfinder(char *current_line, char c);
// char    *ft_strjoin(char *buffer, char *temp);
// size_t  ft_strlen(char *str);

// #endif


#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char    *get_next_line(int fd);

size_t  ft_strlen(char *str);
char    *ft_strjoin(char *buffer, char *point);
int     find_newline(char *s);
char    *extract_line(char *cache);
char    *trim_cache(char *cache);

#endif
