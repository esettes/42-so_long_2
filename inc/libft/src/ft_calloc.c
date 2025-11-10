/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-01 10:37:20 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-01 10:37:20 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;
	size_t	sz;

	if (count == 0u || size == 0u)
		sz = 1u;
	else if (size > SIZE_MAX / count)
		return (NULL);
	else
		sz = count * size;
	ret = malloc(sz);
	if (!ret)
		return (NULL);
	ft_bzero(ret, sz);
	return (ret);
}
