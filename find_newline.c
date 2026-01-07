#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int find_newline (char *s)
// {
//     int i;

//     if (!s)
//         return(-1);

//     i = 0;
//     while (s[i] != '\0')
//     {
//         if(s[i] == '\n')
//             return (i);
//         i++;
//     }
//     return (-1);
// }

// char* extract_line (char *cache)
// {
//     char    *newline;
//     int         i;

//     if (!cache)
//         return (NULL);
    
//     i = 0;
//     while (cache[i] != '\0' && cache[i] != '\n')
//         i++;
    
//     newline = malloc(sizeof(char) * (i + 2));
//     if (!newline)
//         return (NULL);

//     i = 0;
//     while (cache[i] != '\0' && cache[i] != '\n')
//     {
//         newline[i] = cache[i];
//         i++;
//     }

//     if (cache[i] == '\n')
//     {
//         newline[i] = '\n';
//         i++;
//     }
//     newline[i] = '\0';
//     return (newline);
// }

// int main()
// {
//     char *s = "Hello\nDating\nLord";
//     char *n = extract_line(s);
//     printf("%s", n);
// }

int ft_strlen(char* str)
{
    int i;
    i = 0;
    
    while(str[i] != '\0')
    {
        i++;
    }
    return(i);
}

char* trim_cache(char *cache)
{
    char *new_cache;
    int           i;
    int           j;

    if (!cache)
        return (NULL);

    i = 0;
    while (cache[i] != '\0' && cache[i] != '\n')
        i++;

    if (!cache[i])
    {
        free(cache);
        return (NULL);
    }

    i++;

    new_cache = malloc(sizeof(char) * (ft_strlen(cache) - i + 1));
    
    if (!new_cache)
        return (NULL);

    j = 0;
    while (cache[i] != '\0')
    {
        new_cache[j++] = cache[i++];
    }
    new_cache[j] = '\0';
    free(cache);
    return(new_cache);
}

// int main()
// {
//     char *s_literal = "Hello\nDating\nLord";
//     char *s = malloc(strlen(s_literal) + 1);
//     if (!s)
//         return (1);
//     strcpy(s, s_literal);

//     char *n = trim_cache(s);
//     if (n)
//     {
//         printf("%s", n);
//         free(n);
//     }
//     return (0);
// }