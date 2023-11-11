/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:42 by sdell-er          #+#    #+#             */
/*   Updated: 2023/11/11 17:40:18 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char const *s)
{
	int	l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

int	ft_strlcat(char *dst, const char *src, int size)
{
	int	i;
	int	sl;
	int	dl;

	sl = ft_strlen(src);
	if (size == 0)
		return (sl);
	dl = ft_strlen(dst);
	i = 0;
	while (src[i] && dl + i < (size - 1))
	{
		dst[i + dl] = src[i];
		i += 1;
	}
	if (i < size)
		dst[dl + i] = '\0';
	if (dl > size)
		return (sl + size);
	return (dl + sl);
}

void	*ft_memcpy(void *dest, const void *src, int n)
{
	int		i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	int			len;
	char		*buffer;
	char		*line;
	char		*temp;
	static char	*store;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (store == NULL)
	{
		store = malloc(BUFFER_SIZE + 1);
		if (!store)
			return (NULL);
		store[0] = '\0';
	}
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	len = BUFFER_SIZE;
	while (len == BUFFER_SIZE && ft_strchr(store, '\n') == NULL)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len <= 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[len] = '\0';
		temp = malloc(ft_strlen(store) + 1);
		if (!temp)
			return (NULL);
		ft_memcpy(temp, store, ft_strlen(store) + 1);
		free(store);
		store = malloc(ft_strlen(store) + len + 1);
		if (!store)
			return (NULL);
		ft_memcpy(store, temp, ft_strlen(temp) + 1);
		free(temp);
		ft_strlcat(store, buffer, len);
	}
	free(buffer);
	if (ft_strchr(store, '\n') != NULL)
	{
		line = malloc((int)(ft_strchr(store, '\n') - store + 1) + 1);
		if (!line)
			return (NULL);
		ft_memcpy(line, store, (int)(ft_strchr(store, '\n') - store + 1));
		store = ft_strchr(store, '\n') + 1;
	}
	else
	{
		line = malloc(ft_strlen(store) + 1);
		if (!line)
			return (NULL);
		ft_memcpy(line, store, ft_strlen(store) + 1);
		free(store);
		store = NULL;
	}
	return (line);
}
#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd = open("ciao.txt", O_RDONLY), i = 0;
	while(i < 10)
	{
		printf("%s", get_next_line(fd));
		i++;
	}
	close(fd);
	return 0;
}
