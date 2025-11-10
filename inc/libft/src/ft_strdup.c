/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-01 10:39:24 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-01 10:39:24 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		len;
	int		i;
	char	*ret;

	len = ft_strlen(src);
	i = -1;
	ret = malloc(sizeof(char) * len + 1);
	if (!ret)
		return (NULL);
	while (src[++i])
		ret[i] = src[i];
	ret[i] = '\0';
	return (ret);
}
