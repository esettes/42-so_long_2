/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-03 14:22:01 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-03 14:22:01 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	init_output(t_out *o)
{
	o->line = NULL;
	o->line = malloc(1);
	if (!o->line)
		return ;
	o->line[0] = '\0';
	o->nl_pos = -1;
	o->len = 0;
	o->size = 1;
}

void	*f_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s = (const unsigned char *)src;
	unsigned char		*d;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	if (s == d || n == 0u)
		return (dest);
	if (d > s && d < s + n)
	{
		s += n;
		d += n;
		while (n--)
			*--d = *--s;
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}

void	*f_memcpy(void *dest, const void *src, size_t bytes)
{
	size_t				i;
	const unsigned char	*s = (const unsigned char *)src;
	unsigned char		*d;

	if (!dest && !src)
		return (NULL);
	i = 0;
	d = (unsigned char *)dest;
	while (i < bytes)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

void	*ft_realloc(void *old_ptr, size_t oldsize, size_t newsize)
{
	void	*new_ptr;
	size_t	cpy;

	if (newsize == 0)
	{
		free(old_ptr);
		return (NULL);
	}
	if (!old_ptr)
		return (malloc(newsize));
	new_ptr = malloc(newsize);
	if (!new_ptr)
		return (NULL);
	if (oldsize < newsize)
		cpy = oldsize;
	else
		cpy = newsize;
	if (cpy > 0)
		f_memcpy(new_ptr, old_ptr, cpy);
	free(old_ptr);
	return (new_ptr);
}

/**
 * if target == 0, then target = r
 * if target == 1, then target = o
 */
ssize_t	get_pos_nl(t_read *r, t_out *o, int target)
{
	size_t	i;

	if (target == 0)
	{
		i = r->curr;
		while (i < r->end)
		{
			if (r->raw[i] == '\n' || r->raw[i] == '\0')
				return ((ssize_t)i);
			i++;
		}
	}
	else if (target == 1)
	{
		i = 0;
		while (i < o->len)
		{
			if (o->line[i] == '\n' || o->line[i] == '\0')
				return ((ssize_t)i);
			i++;
		}
	}
	return (-1);
}
