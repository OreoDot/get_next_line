#include "get_next_line.h"

char *read_to_cache(int fd, char **cache)
{
	char	*buffer;
	char	*tmp;
	ssize_t	bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);

	bytes_read = 1;
	while (find_newline(*cache) == -1 && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';

		if (!*cache)
			*cache = ft_strjoin("", buffer);
		else
		{
			tmp = ft_strjoin(*cache, buffer);
			free(*cache);
			*cache = tmp;
		}
	}
	free(buffer);
	return (*cache);
}

char *get_next_line(int fd)
{
    static char *cache[1024];
    char        *line;

    if (fd < 0 || fd >= 1024)
        return (NULL);

    cache[fd] = read_to_cache(fd, &cache[fd]);
    if (!cache[fd])
        return (NULL);

    line = extract_line(cache[fd]);
    cache[fd] = trim_cache(cache[fd]);
    return (line);
}
