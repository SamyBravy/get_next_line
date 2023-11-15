/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:42 by sdell-er          #+#    #+#             */
/*   Updated: 2023/11/15 16:19:07 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char const *s)
{
	int	l;

	if (!s)
		return (0);
	l = 0;
	while (s[l])
		l++;
	return (l);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
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

char	*ft_strjoin(char **s1, char *s2)
{
	int		i;
	char		*new;

	new = malloc (sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1));
	if (!new)
	{
		if (*s1)
			free(*s1);
		return (NULL);
	}
	i = 0;
	while (i < ft_strlen(*s1))
	{
		new[i] = (*s1)[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		new[i + ft_strlen(*s1)] = s2[i];
		i++;
	}
	new[i + ft_strlen(*s1)] = '\0';
	if (*s1)
		free(*s1);
	return (new);
}

void	*ft_memcpy(void *dest, const void *src, int n)
{
	int		i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

void	ft_bzero(void *s, int n)
{
	int	i;
	char	*arr;

	arr = (char *) s;
	i = 0;
	while (i < n)
	{
		arr[i] = '\0';
		i++;
	}
}

char	*ft_calloc(int nmemb, int size)
{
	void	*ptr;

	if (!nmemb || !size)
		return (malloc(1));
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

char	*get_next_line(int fd)
{
	int			len;
	int			size;
	int			ctrl;
	char		*buffer;
	char		*line;
	static char	*store = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (store)
			free(store);
		return (NULL);
	}
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
	{
		if (store)
			free(store);
		return (NULL);
	}
	len = BUFFER_SIZE;
	ctrl = 0;
	while (len == BUFFER_SIZE && ft_strchr(store, '\n') == NULL)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len < 0 || (len == 0 && !ctrl))
		{
			if (store)
				free(store);
			free(buffer);
			return (NULL);
		}
		store = ft_strjoin(&store, buffer);
		if (!store)
		{
			free(buffer);
			return (NULL);
		}
		ctrl = 1;
	}
	free(buffer);
	if (ft_strchr(store, '\n') != NULL)
		size = (int)(ft_strchr(store, '\n') - store + 1);
	else
		size = ft_strlen(store);
	line = ft_calloc(size + 1, sizeof(char));
	if (!line)
	{
		free(store);
		return (NULL);
	}
	ft_memcpy(line, store, size);
	store = ft_strchr(store, '\n') + 1;
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
