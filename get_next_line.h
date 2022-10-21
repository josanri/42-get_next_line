/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josesanc <josesanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 09:54:54 by josesanc          #+#    #+#             */
/*   Updated: 2022/09/30 12:13:42 by josesanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_string
{
	char	*str;
	ssize_t	size;
}	t_string;

char		*get_next_line(int fd);
int			ft_shorten(t_string *fd_set[], ssize_t upto, int fd);
int			ft_buff(t_string *res, t_string *fd_set[], int fd);
char		*ft_return_and_free(t_string	*string);
char		*ft_stjon(char *s1, char *s2, ssize_t size_x, ssize_t size_y);
ssize_t		ft_bytestojoin(char *s1, ssize_t end);
char		*ft_readloop(t_string *res, t_string *fd_set[], int fd);
int			ft_aux(t_string *fd_set[], int fd);
char		*ft_free_buff_and_return(t_string *res, t_string *fd_set[], int fd);
char		*ft_null_exit(t_string *res, t_string *fd_set[], int fd);

#endif