/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:21:58 by rstancu           #+#    #+#             */
/*   Updated: 2025/10/06 12:00:16 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_read
{
	char	*raw;
	size_t	curr;
	size_t	end;
	ssize_t	nl_pos;
	int		is_init;
}	t_read;

typedef struct s_out
{
	char	*line;
	ssize_t	nl_pos;
	size_t	len;
	size_t	size;
}	t_out;

ssize_t			get_pos_nl(t_read *r, t_out *o, int target);
void			*f_memmove(void *dest, const void *src, size_t n);
void			*ft_realloc(void *old_ptr, size_t oldsize, size_t newsize);
void			*f_memcpy(void *dest, const void *src, size_t bytes);
char			*get_next_line(int fd);
void			init_output(t_out *o);

#endif
