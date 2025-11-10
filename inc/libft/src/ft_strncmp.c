/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-01 10:38:59 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-01 10:38:59 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	if (n == 0)
		return (0);
	while (*s1 && n - 1 > 0 && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}
