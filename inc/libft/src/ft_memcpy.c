/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-01 10:39:56 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-01 10:39:56 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief used to copy a block of data from a source address to a 
 * destination address.
 * 
 * @param void dest
 * @param void src
 * @param size_t bytes
 */
void	*ft_memcpy(void *dest, const void *src, size_t bytes)
{
	size_t				i;
	const unsigned char	*s;
	unsigned char		*d;

	if (!dest && !src)
		return (NULL);
	i = 0;
	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	while (i < bytes)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
