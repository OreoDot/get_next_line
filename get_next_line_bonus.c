/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolaniya <dolaniya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:19:17 by dolaniya          #+#    #+#             */
/*   Updated: 2026/01/15 17:49:03 by dolaniya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	new_str = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		new_str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new_str[j++] = s2[i++];
	new_str[j] = '\0';
	return (new_str);
}

static char	*extract_line(char *buffer, char *ini_line)
{
	char	*find_newline;
	char	*final_line;
	char	*str_nl;

	find_newline = ft_strchr(buffer, '\n');
	str_nl = ft_substr(buffer, 0, (find_newline - buffer) + 1);
	final_line = ft_strjoin(ini_line, str_nl);
	free(ini_line);
	free(str_nl);
	ft_memmove(buffer, find_newline + 1, ft_strlen(find_newline + 1) + 1);
	return (final_line);
}

int	buffer_prep(char *buffer, char **line)
{
	char		*tmp;

	if (ft_strchr(buffer, '\n'))
		return (1);
	if (buffer[0] == '\0')
		return (0);
	tmp = *line;
	*line = ft_strjoin(tmp, buffer);
	free(tmp);
	buffer[0] = '\0';
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[MAX_BUFFER][BUFFER_SIZE + 1];
	char		*line;
	ssize_t		rd;

	if (fd < 0 || fd >= MAX_BUFFER || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	rd = 1;
	while (rd > 0)
	{
		if (buffer_prep(buffer[fd], &line))
			return (extract_line(buffer[fd], line));
		rd = read(fd, buffer[fd], BUFFER_SIZE);
		if (rd < 0)
			return (free(line), NULL);
		buffer[fd][rd] = '\0';
	}
	return (line);
}
