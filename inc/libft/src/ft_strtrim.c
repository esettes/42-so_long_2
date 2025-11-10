/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-01 10:36:48 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-01 10:36:48 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_char(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * Erases  chars of string 'set' from start and from end of string 's1'
 * since set is in s1, remaining string is returned
 * If s1 or set is NULL, return NULL
 * If s1 only contains chars from set, return empty string
 * Example: s1 = "  \n\t Hello World \t\n  "
 *			set = " \n\t"
 *			return "Hello World"
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*cpy;
	char	*p;
	size_t	i;
	size_t	j;

	if (!s1 || !set)
		return (NULL);
	if (*s1 == 0)
		return (ft_strdup(""));
	i = 0;
	j = ft_strlen(s1) - 1;
	if (!s1)
		return ((char *)s1);
	while (check_char(set, *(char *)(s1 + i)))
		i++;
	while (check_char(set, *(char *)(s1 + j)) && j >= i)
		j--;
	cpy = (char *)malloc(sizeof(char) * (j - i) + 2);
	p = cpy;
	if (!p)
		return (NULL);
	while (i <= j)
		*cpy++ = *(char *)(s1 + i++);
	*cpy = '\0';
	return (p);
}

// int main(int argc, char *argv[])
// {
// 	char *s1;
// 	char *set;
// 	char *res;

// 	if (argc == 3)
// 	{
// 		s1 = argv[1];
// 		set = argv[2];
// 		res = ft_strtrim(s1, set);
// 		printf("String after trim: '%s'\n", res);
// 	}
// 	return (0);
// }
