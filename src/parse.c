/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-02 13:14:51 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-02 13:14:51 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_cell(int32_t *cell, t_map_typos typo)
{
	if (typo == M_WALL)
		*cell = M_WALL;
	else if (typo == M_FLOOR)
		*cell = M_FLOOR;
	else if (typo == M_CEIL)
		*cell = M_CEIL;
	else if (typo == M_LADDER)
		*cell = M_LADDER;
	else if (typo == M_PLATFORM)
		*cell = M_PLATFORM;
	else if (typo == M_LADDER_UP)
		*cell = M_LADDER_UP;
	else if (typo == M_LADDER_DOWN)
		*cell = M_LADDER_DOWN;
}

/**
 * detect wich '1' is wall, ceil, floor, ladder or platform
 */
void	parse_array(int32_t **map, size_t w, size_t h)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while(i < h)
	{
		j = 0;
		while (j < w)
		{
			if (j == 0 || j == w - 1)
				set_cell(&map[i][j], M_WALL);
			else if (i == 0)
				set_cell(&map[i][j], M_CEIL);
			else if (i == h - 1)
			{
				if (map[i - 1][j] == M_LADDER)
					set_cell(&map[i][j], M_LADDER_UP);
			}
			//if (map[i][j] == 1 && map[i + 1] == 1)
			
			else if (map[i][j] == 1)
			{
				
				if ((map[i][j - 1] == 1 && map[i][j + 1] == 1)
					|| (map[i][j - 1] == 1 && map[i][j + 1] == 0)
					||  (map[i][j + 1] == 1 && map[i][j - 1] == 0))
					{
						if ((map[i - 1][j] == 1 || map[i + 1][j] == 1)
							|| (map[i + 1][j] == M_CEIL || map[i - 1][j] == M_FLOOR))
							{
								// INVALID MAP !!!!!!!!!!!!!!!!!!!!!!!!!!
							}
						if (map[i][j] != M_LADDER_DOWN && map[i][j] != M_LADDER_UP)
							set_cell(&map[i][j], M_PLATFORM);
					}
				if (map[i][j - 1] == 0 && map[i][j + 1] == 0)
				{
					set_cell(&map[i][j], M_LADDER);
					if (map[i - 1][j] == 1 && (map[i - 1][j - 1] != 0 || map[i - 1][j + 1] != 0))
						set_cell(&map[i - 1][j], M_LADDER_DOWN);
					if ((map[i + 1][j] == 1 && map[i + 1][j - 1] != 0 && map[i + 1][j + 1] != 0)
						|| (map[i + 1][j + 1] == M_FLOOR && map[i + 1][j - 1] == M_FLOOR))
						set_cell(&map[i + 1][j], M_LADDER_UP);
				}
			}
			// else if (map[i][j] == M_FLOOR)
			// {
			// 	if (map[i - 1][j] == M_LADDER)
			// 		set_cell(&map[i][j], M_LADDER_UP);
			// } 
			j++;
		}
		i++;
	}
}