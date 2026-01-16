/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolaniya <dolaniya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:19:31 by dolaniya          #+#    #+#             */
/*   Updated: 2026/01/15 15:49:58 by dolaniya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	chr_cast;

	i = 0;
	chr_cast = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == chr_cast)
			return ((char *)s + i);
		i++;
	}
	if (!chr_cast && s[i] == '\0')
		return ((char *)s + i);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_substr(char const *str, unsigned int start, size_t cpy_len)
{
	char	*substr;
	size_t	i;

	if (!str)
		return (NULL);
	if (start > ft_strlen(str))
		return (ft_strdup(""));
	if (cpy_len > ft_strlen(str + start))
		cpy_len = ft_strlen(str + start);
	substr = malloc((cpy_len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < cpy_len)
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strdup(const char *s)
{
	char	*dup_str;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s) + 1;
	dup_str = malloc(len);
	if (!dup_str)
		return (NULL);
	while (s[i])
	{
		dup_str[i] = s[i];
		i++;
	}
	dup_str[i] = '\0';
	return ((char *)(dup_str));
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	i = 0;
	if (d > s)
	{
		i = len;
		while (i-- > 0)
			d[i] = s[i];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
