/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   platform_detect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:10:47 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/08 16:24:42 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	is_platform_cell(t_platform *plat, char c, size_t row, size_t col)
{
	if (c == M_PLATFORM || c == M_LADDER_DOWN || c == M_LADDER_UP)
	{
		if (plat)
		{
			if (c == M_LADDER_DOWN || c == M_LADDER_UP)
			{
				plat->pos_ladder.x = col;
				plat->pos_ladder.y = row;
				printf("* * * * * platform cell with ladders: map[%zu][%zu] \n", row, col);

			}
		}
		return (true);
	}
	return (false);
}

static size_t	count_platforms(int32_t **map, t_map *datamap)
{
	size_t	row;
	size_t	col;
	size_t	plats;

	plats = 0;
	row = 0;
	while (row < datamap->height)
	{
		col = 0;
		while (col < datamap->weight)
		{
			if (is_platform_cell(NULL, map[row][col], row, col))
			{
				plats++;
				while (col < datamap->weight && is_platform_cell(NULL, map[row][col], row, col))
					col++;
			}
			else
				col++;
		}
		row++;
	}
	printf("num of platforms: %zu \n", plats);
	return (plats);
}

bool	bresenham_expand(t_platform *plat)
{
	size_t	i = 0;
	int32_t	extra;
	size_t	end;
	size_t	begin;
	size_t	denom;
	size_t	accum;

	extra = plat->size - NUM_PLAT_SPRITES;	// repetitions to distribute
	while (i < NUM_PLAT_SPRITES)
		plat->emit[i++] = 1;
	if (extra <= 0)
		return (false);
	begin = 1;
	if (NUM_PLAT_SPRITES >= 2)
		end = NUM_PLAT_SPRITES - 2;
	else
		end = 0;
	denom = end - begin - 1;
	accum = denom / 2;	
	while (begin <= end)
	{
		accum += extra;
		while (accum >= denom)
		{
			plat->emit[begin] += 1;
			accum -= denom;
		}
		begin++;
	}
	printf("Bresenham distribution:\n");
	i = 0;
	while (i < NUM_PLAT_SPRITES)
	{
		printf("  emit[%zu] = %zu\n", i, plat->emit[i]);
		i++;
	}
	return (true);
}

void	set_pixels_height(t_solong *so, size_t plats)
{
	uint16_t	count_px;
	uint16_t	count_emit;
	uint16_t	iter_emit;

	count_emit = 0;
	count_px = 0;
	iter_emit = 0;
	so->map->plat[plats]->height_px = malloc(sizeof(uint16_t) * so->map->plat[plats]->size);
	if (so->map->plat[plats]->size > NUM_PLAT_SPRITES)
	{
		while (count_px < NUM_PLAT_SPRITES)
		{
			count_emit = so->map->plat[plats]->emit[count_px];
			while (count_emit--)
			{
				so->map->plat[plats]->height_px[iter_emit] = so->map->info_plat.floor_collision_px[count_px];
				printf("collision pixels: %i\n", so->map->plat[plats]->height_px[iter_emit]);
				iter_emit++;
			}
			count_px++;
		}
	}
	else
	{
		while (count_px < so->map->plat[plats]->size)
		{
			so->map->plat[plats]->height_px[count_px] = so->map->info_plat.floor_collision_px[count_px];
			printf("collision pixels: %i\n", so->map->plat[plats]->height_px[iter_emit]);
			count_px++;
		}
	}
}

bool	detect_platforms(t_solong *so, int32_t **map)
{
	size_t	row;
	size_t	col;
	size_t	plats;
	size_t	i = -1;
	size_t	max_plats;
	

	row = 0;
	max_plats = count_platforms(map, so->map);
	so->map->num_platforms = max_plats;
	so->map->plat = malloc(sizeof(t_platform *) * max_plats + 1);
	plats = 0;
	while (++i <= max_plats)
		so->map->plat[i] = NULL;
	i = 0;
	
	while(row < so->map->height)
	{
		col = 0;
		while (col < so->map->weight)
		{
			so->map->plat[plats] =  malloc(sizeof(t_platform));
			while (col < so->map->weight && !is_platform_cell(so->map->plat[plats], map[row][col], row, col))
				col++;
			if (col >= so->map->weight)
				break;
			
			if (!so->map->plat[plats])
				return (free_all(so));
			so->map->plat[plats]->start = col;
			if (map[row][col - 1]  == M_WALL)
			{
				so->map->plat[plats]->is_inverted = false;
			}
			so->map->plat[plats]->pos_start.x = col;
			so->map->plat[plats]->pos_start.y = row;
			while (col < so->map->weight && is_platform_cell(so->map->plat[plats], map[row][col], row, col))
				col++;
			so->map->plat[plats]->end = col - 1;
			so->map->plat[plats]->size = so->map->plat[plats]->end - so->map->plat[plats]->start + 1;
			if (map[row][col] == M_WALL)
			{
				so->map->plat[plats]->is_inverted = true;
				//so->map->plat[plats]->pos_ladder.x = so->map->plat[plats]->size - 1;
			}
			so->map->plat[plats]->pos_end.x = col - 1;
			so->map->plat[plats]->pos_end.y = row;
			// detect platform orientation
			if (!(map[row][col - 1]  == M_WALL) && !(map[row][col] == M_WALL))
			{
				// INVALID MAP !!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			bresenham_expand(so->map->plat[plats]);
			set_pixels_height(so, plats);
			
			// init bool array 
			// volver a recorrer esta línea de start a end y activar bool e ndonde haya escalera
			// so->map->plat[plats]->has_ladder = malloc(sizeof(bool) * so->map->plat[plats]->size);
			// col = so->map->plat[plats]->start;
			// while (col <= so->map->plat[plats]->end)
			// {
			// 	if (map[row][col] == M_LADDER_DOWN || map[row][col] == M_LADDER_UP)
			// 		so->map->plat[plats]->has_ladder[i] = true;
			// 	else
			// 		so->map->plat[plats]->has_ladder[i] = false;
			// 	i++;
			// 	col++;
			// }



			//i = -1;
			//printf("platform %zu -> plat size: %zu \n", plats, so->map->plat[plats]->size);
			// while (++i < NUM_PLAT_SPRITES)
			// 	printf("repeatitions: %zu \n", so->map->plat[plats]->emit[i]);
			plats++;
		}
		
		row++;
	}
	return (true);
}

