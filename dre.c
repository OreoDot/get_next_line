#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int ft_strlen (char *str)
{
    size_t i;

    i = 0;
    while(str[i] != '\0')
    {
        i++;
    }
    return (i);
}

char* ft_strjoin(char* buffer, char* point)
{
    int i;
    int j;
    int len1;
    int len2;

    len1 = ft_strlen(buffer);
    len2 = ft_strlen(point);

    char *newjoin = malloc(sizeof(char) * (len1 + len2 + 1));
    if(!newjoin)
        return(NULL);

    i = 0;
    while(i < len1)
    {
        newjoin[i] = buffer[i];
        i++;
    }

    j = 0;
    while (j < len2)
    {
        newjoin[i + j] = point[j];
        j++;
    }
    newjoin[i + j] = '\0';
    return (newjoin);
}

int main(void)
{
    char *old = "free";
    char *new = "man";

    printf("%s\n", ft_strjoin(old, new));

    printf("%d\n", ft_strlen("ready"));
}