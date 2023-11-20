/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:42 by sdell-er          #+#    #+#             */
/*   Updated: 2023/11/20 12:44:26 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	l;

	if (!s)
		return (0);
	l = 0;
	while (s[l])
		l++;
	return (l);
}

char	*ft_strchr(char *s, int c)
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
		if (*s1 != NULL)
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
	if (*s1 != NULL)
		free(*s1);
	return (new);
}

void	*ft_memcpy(void *dest, void *src, int n)
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
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

char	*ft_substr(char **s, int start, int len)
{
	int		i;
	int		d;
	char		*new;

	if (start + len <= ft_strlen(*s))
		d = len;
	else if (start >= ft_strlen(*s))
		d = 0;
	else
		d = ft_strlen(*s) - start;
	new = malloc(sizeof(char) * (d + 1));
	if (!new)
	{
		free(*s);
		return (NULL);
	}
	i = 0;
	while (d && i < len && (*s)[i])
	{
		new[i] = (*s)[start + i];
		i++;
	}
	new[i] = '\0';
	free(*s);
	return (new);
}

char	*get_next_line(int fd)
{
	int			len;
	int			ctrl;
	char		*buffer;
	static char	*store = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	len = BUFFER_SIZE;
	ctrl = 0;
	while (len == BUFFER_SIZE && ft_strchr(store, '\n') == NULL)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len < 0 || (len == 0 && !ctrl))
		{
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
		len = ft_strchr(store, '\n') - store + 1;
	else
		len = ft_strlen(store);
	buffer = ft_calloc(len + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	ft_memcpy(buffer, store, len);
	if (ft_strchr(store, '\n') != NULL)
	{
		store = ft_substr(&store, len, ft_strlen(store) - len + 1);
		if (!store)
		{
			free(buffer);
			return (NULL);
		}
	}
	else
		free(store);
	return (buffer);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
// 	int fd = open("ciao.txt", O_RDONLY), i = 0;
// 	char *s;
// 	while(i < 10)
// 	{
// 		s = get_next_line(fd);
// 		if(s)
// 			printf("%s", s);
// 		i++;
// 		if (s != NULL)
// 			free(s);
// 	}
// 	close(fd);
// 	return 0;
// }
