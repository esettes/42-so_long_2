/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:23:16 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/02 19:43:49 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	debug_platforms(t_solong solong)
{
	size_t j = 0;

	while (j < solong.map->num_platforms)
	{
		printf("Platform %zu:\n", j);
		printf("  - Size: %zu\n", solong.map->plat[j]->size);
		printf("  - buffer_top: %p\n", (void*)solong.map->plat[j]->buffer_top);
		printf("  - buffer_under: %p\n", (void*)solong.map->plat[j]->buffer_under);
		
		if (solong.map->plat[j]->buffer_top)
		{
			size_t k = 0;
			while (k < solong.map->plat[j]->size)
			{
				if (!solong.map->plat[j]->buffer_top[k])
					printf("  - WARNING: buffer_top[%zu] is NULL\n", k);
				if (!solong.map->plat[j]->buffer_under[k])
					printf("  - WARNING: buffer_under[%zu] is NULL\n", k);
				k++;
			}
		}
		j++;
	}
}

bool	print_platforms(t_solong solong)
{
	size_t j;

	j = 0;
	printf("PLATFORMS DETECTED AT CELLS: \n");
	while (j < solong.map->num_platforms)
	{
		printf("Platform %zu: Start(%x, %x) - End(%x, %x) Size: %zu \n", j,
			solong.map->plat[j]->pos_start.x, solong.map->plat[j]->pos_start.y,
			solong.map->plat[j]->pos_end.x, solong.map->plat[j]->pos_end.y,
			solong.map->plat[j]->size);
		j++;
	}
	j = 0;
	while (j < solong.map->num_platforms)
	{
		size_t k = 0;

		printf("Rendering platform %zu with %zu sprites\n", j, solong.map->plat[j]->size);

		while (k < solong.map->plat[j]->size)
		{
			if (!solong.map->plat[j]->buffer_top[k])
			{
				printf("ERROR: plat[%zu]->buffer_top[%zu] is NULL\n", j, k);
				return (1);
			}
			if (!solong.map->plat[j]->buffer_under[k])
			{
				printf("ERROR: plat[%zu]->buffer_under[%zu] is NULL\n", j, k);
				return (1);
			}
			
			// top
			if (mlx_image_to_window(solong.mlx, solong.map->plat[j]->buffer_top[k], 
				(solong.map->plat[j]->pos_start.x * TILESIZE) + (TILESIZE * k), (solong.map->plat[j]->pos_start.y * TILESIZE)) == -1)
			{
				printf("ERROR: Failed to render buffer_top[%zu][%zu]\n", j, k);
				return (1);
			}
			
			// under
			if (mlx_image_to_window(solong.mlx, solong.map->plat[j]->buffer_under[k], 
				(solong.map->plat[j]->pos_start.x * TILESIZE) + (TILESIZE * k), (solong.map->plat[j]->pos_start.y * TILESIZE) + TILESIZE) == -1)
			{
				printf("ERROR: Failed to render buffer_under[%zu][%zu]\n", j, k);
				return (1);
			}
			
			k++;
		}
		j++;
	}
	return (true);
}

void 	print_floor(t_solong solong)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < solong.map->height)
	{
		j = 0;
		while (j < solong.map->weight)
		{
			if (i == solong.map->height - 1)
			{
				if (!solong.map->floor[j])
				{
					printf("ERROR: floor[%zu] is NULL\n", j);
					return ;
				}
				if (mlx_image_to_window(solong.mlx, solong.map->floor[j], j * TILESIZE, i * TILESIZE) == -1)
				{
					printf("ERROR: Failed to render floor[%zu] at position (%zu, %zu)\n", j, j * TILESIZE, i * TILESIZE);
					return ;
				}
			}
			j++;
		}
		i++;
	}
}