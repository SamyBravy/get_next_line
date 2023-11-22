/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:42 by sdell-er          #+#    #+#             */
/*   Updated: 2023/11/22 18:15:32 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
// #include "get_next_line_utils.c"

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

char	*ft_substr(char **s, int start)
{
	int			i;
	int			d;
	char		*new;

	if (start < ft_strlen(*s))
		d = ft_strlen(*s) - start;
	else
		d = 0;
	new = malloc(sizeof(char) * (d + 1));
	if (!new)
	{
		free(*s);
		return (NULL);
	}
	i = 0;
	while (i < d)
	{
		new[i] = (*s)[start + i];
		i++;
	}
	new[i] = '\0';
	free(*s);
	return (new);
}

int	get_current_line(int fd, char **store, char **buffer, int len)
{
	while (len == BUFFER_SIZE && ft_strchr(*store, '\n') == NULL)
	{
		ft_bzero(*buffer, BUFFER_SIZE + 1);
		len = read(fd, *buffer, BUFFER_SIZE);
		if (len < 0 || (len == 0 && !ft_strlen(*store)))
		{
			free(*buffer);
			if (*store)
			{
				free(*store);
				*store = NULL;
			}
			return (0);
		}
		else
		{
			*store = ft_strjoin(store, *buffer);
			if (!*store)
			{
				free(*buffer);
				return (0);
			}
		}
	}
	return (1);
}

int	set_current_line(char **store, char **buffer)
{
	int	len;

	if (ft_strchr(*store, '\n') != NULL)
		len = ft_strchr(*store, '\n') - *store + 1;
	else
		len = ft_strlen(*store);
	*buffer = ft_calloc(len + 1, sizeof(char));
	if (!*buffer)
		return (0);
	ft_memcpy(*buffer, *store, len);
	if (ft_strchr(*store, '\n') != NULL)
	{
		*store = ft_substr(store, ft_strlen(*buffer));
		if (!*store)
		{
			free(*buffer);
			return (0);
		}
	}
	else
	{
		free(*store);
		*store = NULL;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*store[20000];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!get_current_line(fd, store + fd, &buffer, BUFFER_SIZE))
		return (NULL);
	free(buffer);
	if (!set_current_line(store + fd, &buffer))
		return (NULL);
	return (buffer);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
// 	int fd = open("big_line_no_nl", O_RDONLY), i = 0;
// 	char *s;
// 	while(1)
// 	{
// 		s = get_next_line(fd);
// 		if(s)
// 			printf("%s", s);
// 		else
// 			break;
// 		i++;
// 		if (s != NULL)
// 			free(s);
// 	}
// 	close(fd);
// 	return 0;
// }
