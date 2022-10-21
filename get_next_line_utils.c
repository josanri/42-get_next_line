/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josesanc <josesanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 10:43:44 by josesanc          #+#    #+#             */
/*   Updated: 2022/09/30 12:13:49 by josesanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Reduces the size of the buffer from the first \n
Returns -1 when error at malloc */
int	ft_shorten(t_string *fd_set[], ssize_t upto, int fd)
{
	char	*shortened;
	ssize_t	aux_f;
	ssize_t	aux_d;

	aux_f = 0;
	aux_d = upto;
	if ((fd_set[fd])->size == upto)
		return (ft_aux(fd_set, fd));
	shortened = (char *) malloc ((fd_set[fd])->size - upto);
	if (shortened == NULL)
		return (-1);
	while (aux_d < (fd_set[fd])->size)
	{
		shortened[aux_f++] = (fd_set[fd])->str[aux_d];
		aux_d++;
	}
	free((fd_set[fd])->str);
	(fd_set[fd])->str = shortened;
	(fd_set[fd])->size -= upto;
	return (0);
}

int	ft_buff(t_string *res, t_string *fd_set[], int fd)
{
	ssize_t	end;

	end = ft_bytestojoin(fd_set[fd]->str, fd_set[fd]->size);
	res->str = ft_stjon(res->str, fd_set[fd]->str, res->size, end);
	if (res->str == NULL || ft_shorten(fd_set, end, fd) != 0)
	{
		if (res->str != NULL)
		{
			free(res->str);
			res->str = NULL;
		}
		if (fd_set[fd] != NULL)
		{
			if (fd_set[fd]->str != NULL)
				free(fd_set[fd]->str);
			free(fd_set[fd]);
			fd_set[fd] = NULL;
		}
		return (-1);
	}
	res->size += end;
	return (0);
}

char	*ft_null_exit(t_string *res, t_string *fd_set[], int fd)
{
	if (res != NULL)
	{
		if (res->str != NULL)
			free(res->str);
		res->str = NULL;
	}
	if (fd_set[fd] != NULL)
	{
		if (fd_set[fd]->str != NULL)
			free(fd_set[fd]->str);
		free(fd_set[fd]);
		fd_set[fd] = 0;
	}
	return (NULL);
}

char	*ft_free_buff_and_return(t_string *res, t_string *fd_set[], int fd)
{
	if (fd_set[fd] != NULL)
	{
		if (fd_set[fd]->str != NULL)
			free(fd_set[fd]->str);
		free(fd_set[fd]);
		fd_set[fd] = 0;
	}
	return (res->str);
}

/* Reading loop */
char	*ft_readloop(t_string *res, t_string *fd_set[], int fd)
{
	ssize_t	b_r;
	ssize_t	b_j;

	while (1)
	{
		b_r = read(fd, fd_set[fd]->str, BUFFER_SIZE);
		if (b_r == 0)
			return (ft_free_buff_and_return(res, fd_set, fd));
		if (b_r == -1)
			return (ft_null_exit(res, fd_set, fd));
		fd_set[fd]->size = b_r;
		b_j = ft_bytestojoin(fd_set[fd]->str, fd_set[fd]->size);
		res->str = ft_stjon(res->str, fd_set[fd]->str, res->size, b_j);
		if (res->str == NULL)
			return (ft_null_exit(res, fd_set, fd));
		res->size += b_j;
		if (b_j < b_r || b_r < BUFFER_SIZE || res->str[res->size - 1] == '\n')
		{
			if (ft_shorten(fd_set, b_j, fd) == -1)
				return (ft_null_exit(res, fd_set, fd));
			return (ft_return_and_free(res));
		}
	}
}
