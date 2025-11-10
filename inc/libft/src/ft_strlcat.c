/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-01 10:39:14 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-01 10:39:14 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	const char	*s;
	char		*d;
	size_t		n;
	size_t		destlen;
	size_t		srclen;

	s = src;
	d = dst;
	n = size;
	while (n && *d)
	{
		d++;
		n--;
	}
	destlen = (size_t)(d - dst);
	srclen = ft_strlen(s);
	if (n == 0)
		return (destlen + srclen);
	while (--n && *s)
		*d++ = *s++;
	*d = '\0';
	return (destlen + srclen);
}
