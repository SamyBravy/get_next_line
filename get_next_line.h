/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:55:40 by sdell-er          #+#    #+#             */
/*   Updated: 2023/12/11 15:06:07 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

int		ft_strlen(char *s);

char	*get_next_line(int fd);
char	*ft_calloc(int nmemb, int size);
char	*ft_strjoin(char **s1, char *s2);
char	*ft_strchr(char *s, int c);

void	ft_bzero(void *s, int n);

#endif