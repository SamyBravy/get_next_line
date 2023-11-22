/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:43:25 by sdell-er          #+#    #+#             */
/*   Updated: 2023/11/22 18:09:46 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

void	ft_bzero(void *s, int n)
{
	int		i;
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

char	*ft_strjoin(char **s1, char *s2)
{
	int			i;
	char		*new;

	new = malloc (sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1));
	if (!new)
	{
		if (*s1 != NULL)
			free(*s1);
		return (NULL);
	}
	i = -1;
	while (++i < ft_strlen(*s1))
		new[i] = (*s1)[i];
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
