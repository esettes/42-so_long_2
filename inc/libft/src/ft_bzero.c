/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-01 10:37:36 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-01 10:37:36 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief erases the data in the n bytes of the memory starting at the location
 * pointed to by s, by writing zeros (bytes containing '\0') to that area.
 * 
 * @param size_t n Number of bytes to set to 0.
 * @param void *s Pointer to first location to fill.
 */
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = 0u;
}
