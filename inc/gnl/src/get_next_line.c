/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:21:50 by rstancu           #+#    #+#             */
/*   Updated: 2025/10/06 12:04:14 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	copy_to_line(t_read *r, t_out *o, size_t n, size_t sel)
{
	if (o->size < o->len + n + 1)
	{
		o->line = ft_realloc(o->line, o->size, o->size + n + 1);
		if (!o->line)
			return ;
		o->size = o->size + n + 1;
	}
	f_memcpy(o->line + o->len, r->raw + r->curr, n);
	o->len = o->len + n;
	o->line[o->len] = '\0';
	if (sel == 1)
		r->curr = r->curr + r->nl_pos - r->curr + 1;
	else
		r->curr = r->end;
}

size_t	check_raw_space(t_read *r, t_out *o)
{
	size_t	n;

	if (r->curr > 0 && (r->end + BUFFER_SIZE) > BUFFER_SIZE)
	{
		f_memmove(r->raw, r->raw + r->curr, r->end - r->curr);
		r->end = r->end - r->curr;
		r->curr = 0;
	}
	else if (r->curr == 0 && (r->end + BUFFER_SIZE) > BUFFER_SIZE)
	{
		n = r->end - r->curr;
		if (o->size < o->len + r->end + 1)
		{
			o->line = ft_realloc(o->line, o->size, o->size + r->end + 1);
			if (!o->line)
				return (0);
			o->size = o->size + r->end + 1;
		}
		f_memcpy(o->line + o->len, r->raw, r->end);
		o->len = o->len + n;
		o->line[o->len + n] = '\0';
		r->end = 0;
	}
	return (1);
}

ssize_t	check_read(t_read *r, t_out *o, int fd)
{
	ssize_t	bytes;

	bytes = read(fd, &r->raw[r->end], BUFFER_SIZE);
	if (bytes < 0)
	{
		free(o->line);
		free(r->raw);
		r->is_init = 0;
		return (-1);
	}
	else if (bytes == 0 && o->len <= 0)
	{
		free(o->line);
		free(r->raw);
		r->is_init = 0;
		return (-1);
	}
	else if (bytes == 0 && o->len > 0)
	{
		free(r->raw);
		r->is_init = 0;
		return (0);
	}
	return (bytes);
}

char	*read_bytes(int fd, t_read *r, t_out *o)
{
	ssize_t	bytes;

	while (1)
	{
		r->nl_pos = get_pos_nl(r, o, 0);
		if (r->nl_pos >= 0)
		{
			copy_to_line(r, o, r->nl_pos - r->curr + 1, 1);
			return (o->line);
		}
		else if (r->nl_pos < 0 && r->end > r->curr)
			copy_to_line(r, o, r->end - r->curr, 0);
		if (check_raw_space(r, o) == 0)
			return (NULL);
		if (r->nl_pos >= 0)
			continue ;
		bytes = check_read(r, o, fd);
		if (bytes < 0)
			return (NULL);
		if (bytes == 0 && o->len > 0)
			return (o->line);
		r->end = r->end + (size_t)bytes;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_read	r;
	t_out			o;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 1024)
		return (NULL);
	init_output(&o);
	if (!o.line)
		return (NULL);
	if (r.is_init != 1)
	{
		r.raw = malloc(BUFFER_SIZE);
		if (!r.raw)
			return (NULL);
		r.curr = 0;
		r.end = 0;
		r.nl_pos = -1;
		r.is_init = 1;
	}
	o.line = read_bytes(fd, &r, &o);
	if (o.line == NULL)
		return (NULL);
	return (o.line);
}

//__attribute__((weak))
// int main(int argc, char **argv)
// {
//     char    *line;
//     int     fd;

// 	fd = open (argv[1], O_RDONLY);
// 	if (fd > 0)
// 	{
// 		printf("fd: %i\n", fd);
// 		while (1)
// 		{
// 			line = get_next_line(fd);
// 			if (line == NULL)
// 				break;
// 			printf ("%s", line);
// 			free (line);
// 		}
// 		close(fd);
// 	}
//     return (0);
// }
