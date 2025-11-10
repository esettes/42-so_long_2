/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-01 10:37:15 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-01 10:37:15 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Find the first occurrence of the character c
 * in the string pointed to by the argument str.
 */
char	*ft_strchr(const char *str, int c)
{
	char	*s;

	s = (char *)str;
	if (c > 255)
		c = c % 256;
	while (*s && *s != c)
		s++;
	if (*s == c)
		return (s);
	return (NULL);
}

// int main()
// {
// 	const char *s = "tripouille";
// 	int c = 't' + 256;
// 	char *result = ft_strchr(s, c);
// 	if (result)
// 		printf("Character '%c' found at position: %ld\n", c, result - s);
// 	else
// 		printf("Character '%c' not found in the string.\n", c);
// 	return 0;
// }