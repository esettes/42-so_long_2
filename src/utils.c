/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:09:57 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/02 19:45:10 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	resize_pixels(xpm_t *xpm, uint32_t new_w, uint32_t new_h)
{
	uint8_t			*dst;
	uint32_t		sx;
	uint32_t		sy;
	const uint8_t	*s;
	uint8_t			*d;
	uint32_t		x;
	uint32_t		y;
	uint8_t			*old;

	y = 0;
	dst = (uint8_t *)malloc((size_t)new_w * new_h * 4);
	if (!dst)
		return (false);
	while (y < new_h)
	{
		x = 0;
		sy = (uint32_t)((uint64_t)y * xpm->texture.height / new_h);
		while (x < new_w)
		{
			sx = (uint32_t)((uint64_t)x * xpm->texture.width / new_w);
			s = &xpm->texture.pixels[((uint64_t)sy * xpm->texture.width + sx) * 4];
			d = &dst[((uint64_t)y * new_w + x) * 4];
			d[0] = s[0];
			d[1] = s[1];
			d[2] = s[2];
			d[3] = s[3];
			x++;
		}
		y++;
	}
	old = xpm->texture.pixels;
	xpm->texture.pixels = dst;
	xpm->texture.height = new_h;
	xpm->texture.width = new_w;
	free(old);
	return (true);
}
