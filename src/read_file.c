/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:46:01 by rstancu           #+#    #+#             */
/*   Updated: 2025/11/13 11:18:07 by settes           ###   ########.fr       */
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
			|| line[i] == 'C' || line[i] == 'E' || line[i] == '\n'))
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
	if (so->map->num_exits != 1 || so->map->num_collects < 1)
	{
		ft_putendl_fd("Error: Invalid number of collectibles or exits.", 2);
		return (false);
	}
	
	return (true);
}
void	free_map_from_index(t_solong *so, size_t k)
{
	size_t	i;

	if (so->map->arr)
	{
		i = 0;
		while (i < k)
		{
			if (so->map->arr[i] != NULL)
				free(so->map->arr[i]);
			i++;
		}
		free(so->map->arr);
	}
}


bool	parse_line(t_solong *so, char *line, size_t k, t_pos *playerpos)
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
		if (line[j] == '1')
			so->map->arr[k][j] = 1;
		else if (line[j] == 'P')
		{
			playerpos->x = (double)(j * TILESIZE);
			playerpos->y = (double)(k * TILESIZE);
			so->player.render_pos.x = playerpos->x;
			so->player.render_pos.y = playerpos->y;
			so->map->arr[k][j] = M_PLAYER;
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
		else
			so->map->arr[k][j] = M_SPACE;
		j++;
	}
	return (true);
}

ssize_t	check_lines_lenght(int32_t fd, t_solong *so)
{
	char	*line;
	size_t	last_len;
	ssize_t	lines;
	bool	same;
	size_t	len;

	lines = -1;
	same = true;
	line = get_next_line(fd);
	if (!line)
		return (lines);
	so->map->width = ft_strlen(line);
	if (line[so->map->width - 1] == '\n')
		so->map->width--;
	lines = 1;
	while (1)
	{
		last_len = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (line[len - 1] != '\n')
		{
			ft_putendl_fd("Error: Map need NL at last line.", 2);
			return (-1);
		}
		if (len != last_len)
			same = false;
		lines++;
	}
	if (!same)
		return (-1);
	return (lines);
}

bool	read_file(t_solong *so, char *file)
{
	int32_t	fd;
	char	*line;
	size_t	k;
	ssize_t	lines;

	k = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (free_all(so));
	lines = check_lines_lenght(fd, so);
	close(fd);
	if (lines < 1)
	{
		ft_putendl_fd("Error: Invalid map. Inconsistent line lengths.", 2);
		return (false);
	}
	so->map->arr = malloc(sizeof(int32_t *) * lines);
	if (!so->map->arr)
	{
		free(so->map->arr);
		return (false);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0 || !so->map->arr)
	{
		free_map(so->map, so->mlx);
		return (false);
	}
	while ((line = get_next_line(fd)))
	{
		if (!is_valid_line(line) || !parse_line(so, line, k, &so->player.pos))
		{
			free(line);
			close(fd);
			free_map_from_index(so, k);
			return (false);
		}
		k++;
		free(line);
	}
	if (!check_num_elemets(so))
	{
		free_map_from_index(so, k + 1);
		return (false);
	}
	so->map->height = lines;
	close(fd);
	return (true);
}

