/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josesanc <josesanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 09:53:48 by josesanc          #+#    #+#             */
/*   Updated: 2022/09/29 16:45:52 by josesanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

/* Frees the struct while returning the string */
char	*ft_return_and_free(t_string	*string)
{
	char	*res;

	res = string->str;
	if (string->size <= 0)
	{
		free(string->str);
		return (NULL);
	}	
	return (res);
}

int	ft_aux(t_string *fd_set[], int fd)
{
	if (fd_set[fd] != NULL)
	{
		if (fd_set[fd]->str != NULL)
			free(fd_set[fd]->str);
		free((fd_set[fd]));
		fd_set[fd] = 0;
	}
	return (0);
}

/* Joins two strings */
char	*ft_stjon(char *s1, char *s2, ssize_t size_x, ssize_t size_y)
{
	ssize_t	counterx;
	ssize_t	countery;
	char	*res;

	res = (char *) malloc(size_x + size_y + 1);
	if (res == NULL)
	{
		if (s1 != NULL)
			free(s1);
		return (NULL);
	}
	counterx = -1;
	countery = -1;
	while (++counterx < size_x)
		res[counterx] = s1[counterx];
	while (++countery < size_y)
		res[counterx + countery] = s2[countery];
	res[counterx + countery] = 0;
	free(s1);
	return (res);
}

/* Locates returns the number of bytes to join */
ssize_t	ft_bytestojoin(char *s1, ssize_t end)
{
	ssize_t	res;

	res = 0;
	while (res < end && s1[res] != '\n')
		res++;
	if (res == end)
		return (res);
	else
		return (res + 1);
}

/* Get next line function is composed by a static array of
1024 length in which each position corresponds to a fd string */
char	*get_next_line(int fd)
{
	static t_string	*fd_set[1024];
	t_string		res;

	if (fd < 0 || fd > 1023)
		return (NULL);
	res.str = NULL;
	res.size = 0;
	if (fd_set[fd] != NULL)
	{
		if (ft_buff(&res, fd_set, fd) != 0 || res.str[res.size - 1] == '\n')
			return (ft_return_and_free(&res));
	}
	fd_set[fd] = (t_string *) malloc (sizeof(t_string));
	if (fd_set[fd] == NULL)
		return (ft_null_exit(&res, fd_set, fd));
	fd_set[fd]->str = (char *)malloc (BUFFER_SIZE);
	if (fd_set[fd]->str == NULL)
		return (ft_null_exit(&res, fd_set, fd));
	return (ft_readloop(&res, fd_set, fd));
}
