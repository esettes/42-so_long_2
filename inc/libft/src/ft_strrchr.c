/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-01 10:37:26 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-01 10:37:26 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;
	int		ret;

	str = (char *)s;
	i = 0;
	ret = 0;
	if (c > 255)
		c = c % 256;
	while (str[i])
	{
		if (str[i] == c)
			ret = i;
		i++;
	}
	if (c == 0)
		return (&str[i]);
	if (ret == 0 && str[ret] != c)
		return (NULL);
	return (&str[ret]);
}

// int main()
// {
// 	const char *str = "tripouille";
// 	int c = 0;

// 	char *result = ft_strrchr(str, c);
// 	if (result)
// 	{
// 		printf("last '%c' in \"%s\" in pos: %ld\n", c, str, result - str);
// 	}
// 	return 0;
// }
