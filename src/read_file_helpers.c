/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-17 13:31:29 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-17 13:31:29 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_valid_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!(line[i] == '1' || line[i] == '0' || line[i] == 'P'
				|| line[i] == 'C' || line[i] == 'E' || line[i] == '\n'
				|| line[i] == 'N'))
		{
			ft_putendl_fd("Error: Invalid character in map.", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_num_elemets(t_solong *so)
{
	if (so->map->num_exits != 1 || so->map->num_collects < 1
		|| so->player.num_characters != 1)
	{
		ft_putendl_fd("Error: Invalid number of collectibles or exits.", 2);
		return (false);
	}
	return (true);
}

void	free_map_from_index(t_solong *so, size_t k)
{
	size_t	i;

	printf("k=%zu\n", k);
	if (so->map->arr)
	{
		i = 0;
		while (i < k)
		{
			free(so->map->arr[i]);
			i++;
		}
		free(so->map->arr);
	}
}

void	set_cell(t_solong *so, char *line, size_t k, size_t j)
{
	if (line[j] == '1')
		so->map->arr[k][j] = 1;
	else if (line[j] == 'P')
	{
		so->player.pos.x = (double)(j * TILESIZE);
		so->player.pos.y = (double)(k * TILESIZE);
		so->player.render_pos.x = so->player.pos.x;
		so->player.render_pos.y = so->player.pos.y;
		so->map->arr[k][j] = M_PLAYER;
		so->player.num_characters++;
	}
	else if (line[j] == 'C')
	{
		so->map->num_collects++;
		so->map->arr[k][j] = M_COLLECTIBLE;
	}
	else if (line[j] == 'E')
	{
		so->map->exit_pos.x = (double)j;
		so->map->exit_pos.y = (double)k;
		so->map->arr[k][j] = M_EXIT;
		so->map->num_exits++;
	}
	else if (line[j] == 'N')
	{
		so->map->exit_pos.x = (double)j;
		so->map->exit_pos.y = (double)k;
		so->map->arr[k][j] = M_ENEMY;
		so->num_enemies++;
	}
	else
		so->map->arr[k][j] = M_SPACE;
}

bool	parse_line(t_solong *so, char *line, size_t k)
{
	size_t	j;
	size_t	len;

	len = ft_strlen(line);
	if ((len > 0) && (line[len - 1] == '\n'))
		len--;
	so->map->arr[k] = malloc(sizeof(int32_t) * len);
	if (!so->map->arr[k])
		return (false);
	j = 0;
	while (j < len)
	{
		set_cell(so, line, k, j);
		j++;
	}
	return (true);
}
