/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:39:53 by rstancu           #+#    #+#             */
/*   Updated: 2025/10/19 13:20:56 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief same as memcpy but handling cases when source and destination
 * addresses are overlapping. If overlap, pointers are positioned at the end
 * and starts copying backwards.
 * 
 * @param void dest
 * @param void src
 * @param size_t n
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
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

// __attribute__((weak))
// int	main(void)
// {
// 	char	*greed;
// 	char	*ptr;
// 	size_t	len;

// 	len = 20;
// 	greed = malloc(100);
// 	ptr = ft_memmove(greed + 5, greed, 10);
// 	return (0);
// }
