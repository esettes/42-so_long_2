/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-01 10:37:32 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-01 10:37:32 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (len > (unsigned int)ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i++] = s[start++];
	}
	ret[i] = '\0';
	return (ret);
}

// int main()
// {
// 	const char *str = "Hello World";
// 	unsigned int start = 15;
// 	size_t len = 5;

// 	char *substr = ft_substr(str, start, len);
// 	if (substr)
// 	{
// 		printf("%s\n", substr);
// 		free(substr);
// 	}
// 	return 0;
// }