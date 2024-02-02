/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:42 by sdell-er          #+#    #+#             */
/*   Updated: 2024/02/02 17:53:28 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
#include "get_next_line_utils.c"
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
*/

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

int	fill_store(int fd, char **store, char **buffer, int len)
{
	if (ft_strchr(*store, '\n') != NULL)
		return (1);
	while (len == BUFFER_SIZE && ft_strchr(*buffer, '\n') == NULL)
	{
		ft_bzero(*buffer, BUFFER_SIZE + 1);
		len = read(fd, *buffer, BUFFER_SIZE);
		if (len < 0 || (len == 0 && !ft_strlen(*store)))
		{
			if (*store && !len)
			{
				free(*store);
				*store = NULL;
			}
			return (0);
		}
		*store = ft_strjoin(store, *buffer);
		if (!*store)
			return (0);
	}
	return (1);
}

char	*set_current_line(char **store, char *new_line_index, int len)
{
	char	*buffer;

	buffer = ft_calloc(len + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	ft_memcpy(buffer, *store, len);
	if (new_line_index != NULL)
	{
		*store = ft_substr(store, ft_strlen(buffer));
		if (!*store)
		{
			free(buffer);
			return (NULL);
		}
	}
	if (new_line_index == NULL || (*store && **store == 0))
	{
		free(*store);
		*store = NULL;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*new_line_index;
	char		*buffer;
	static char	*store = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	if (!fill_store(fd, &store, &buffer, BUFFER_SIZE))
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	new_line_index = ft_strchr(store, '\n');
	if (new_line_index != NULL)
		return (set_current_line(&store, new_line_index,
				new_line_index - store + 1));
	return (set_current_line(&store, new_line_index, ft_strlen(store)));
}
/*
int main()
{
	int fd;
	char *line;
	clock_t start, end;
    double cpu_time_used;

	line = NULL;
	fd = open("big_line_no_nl", O_RDONLY);
	start = clock();
	
	get_next_line(fd);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken: %f seconds\n", cpu_time_used);
	close(fd);
	
}

int main()
{
	int fd = open("big_line_no_nl", O_RDONLY), i = 0;
	char *s;
	while(1)
	{
		s = get_next_line(fd);
		if(s)
			printf("%s", s);
		else
			break;
		i++;
		if (s != NULL)
			free(s);
	}
	close(fd);
	return 0;
}
*/
