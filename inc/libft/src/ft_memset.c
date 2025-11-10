/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-01 10:39:48 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-01 10:39:48 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Ft_memset() takes a pointer to a memory location, a value to set, and the
 * number of bytes to set, and returns a pointer to the memory location
 * 
 * @param void p This is the pointer to the memory area to be filled.
 * @param int val the value to be set
 * @param size_t bytes The number of bytes to be set to the value c.
 * 
 * @return A pointer to the memory area s.
 */
void	*ft_memset(void *p, int val, size_t bytes)
{
	unsigned char	*s;

	s = (unsigned char *)p;
	while (bytes--)
		*s++ = (unsigned char)val;
	return (p);
}
