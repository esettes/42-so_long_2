/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-07 17:03:46 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-07 17:03:46 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_collision_flags(t_solong *so)
{
	int16_t			i;
	int16_t			j;
	t_tile_flags	f;
	int32_t			cell;

	i = 0;
	j = 0;
	so->map->collision_map = malloc(sizeof(uint16_t *) * so->map->height);
	while (i < (int16_t	)so->map->height)
	{
		j = 0;
		f = TF_EMPTY;
		so->map->collision_map[i] = malloc(sizeof(uint16_t) * so->map->weight);
		while (j < (int16_t	)so->map->weight)
		{
			cell = so->map->arr[i][j];
			if (cell == 1)
			{
				f |= TF_PLATFORM_TOP;
			}
			else if (cell == 2)
			{
				f |= TF_LADDER_UP;
			}
			else if (cell == 3)
			{
				f |= TF_LADDER_DOWN;
			}
			else if (cell == 4)
			{
				f |= TF_LADDER;
			}
			else if (cell == 5 || cell == 6 || cell == 7)
			{
				f |= TF_SOLID_FULL;
			}
			so->map->collision_map[i][j] = f;
			j++;
		}
		i++;
	}
}
