/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-01 10:36:52 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-01 10:36:52 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * locates the first occurrence of the  null-terminated string little in the
 * string big, where not more than len characters are searched.
 * 
 * @return If little is an empty string, big is returned; if little	occurs
 * nowhere in big, NULL is returned; otherwise a pointer to the first character
 * of the first occurrence of little is returned
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = -1;
	x = len;
	if (little[0] == '\0')
		return ((char *)big);
	if (!big && len == 0)
		return (NULL);
	while (big[++i] && x)
	{
		j = 0;
		x = len - i;
		if (big[i] == little[j])
		{
			while (little[j] && big[j + i] && (big[i + j] == little[j]) && x--)
				j++;
			if (!little[j])
				return ((char *)&big[i]);
		}
	}
	return (NULL);
}
