/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-31 17:46:01 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-31 17:46:01 by rstancu          ###   ########.fr       */
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
				return (false);
			}
		i++;
	}
	return (true);
}

bool	parse_line(t_solong *so, char *line, size_t k, t_pos *playerpos)
{
	size_t	i;
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
		else if (line[j] == '0' || line[j] == 'C' || line[j] == 'P' ||  line[j] == 'E')
		{
			if (line[j] == 'P')
			{
				playerpos->x = (double)(j * TILESIZE);
				playerpos->y = (double)(k * TILESIZE);
				printf("parse line player pos x: %f, y: %f\n", so->player.pos.x, so->player.pos.y);
			}
			if (line[j] == 'C')
			{
				//so->map->num_collectibles++;
			}
			if (line[j] == 'E')
			{
				// enemyes
			}
			so->map->arr[k][j] = 0;
		}
		else 
		{
			return (false);
		}
		j++;
	}
	i = 0;
	while (i < len)
	{
		printf("%i", so->map->arr[k][i]);
		i++;
	}
	printf("\n");
	return (true);
}

bool	read_file(t_solong *so, char *file)
{
	int32_t	fd;
	char	*line;
	size_t	k;
	size_t	lines;

	lines = 0;
	k = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		//return (free_all(so));
		return (1);
	while ((line = get_next_line(fd)))
	{
		lines++;
		free(line);
	}
	close(fd);
	so->map->original_num_lines = lines;
	so->map->arr = malloc(sizeof(int32_t *) * lines);
	fd = open(file, O_RDONLY);
	if (fd < 0 || !so->map->arr)
		//return (free_all(so));
		return (1);
	while ((line = get_next_line(fd)))
	{
		so->map->weight = ft_strlen(line) - 1;
		if (!is_valid_line(line) || !parse_line(so, line, k, &so->player.pos))
		{
			free(line);
			close(fd);
			//return (free_all(so));
			return (1);
		}
		k++;
		free(line);
	}
	close(fd);
	so->map->height = lines;
	printf("\n");
	//parse_array(so->map->arr, so->map->weight, so->map->height);
	size_t i = 0;
	size_t j = 0;
	while (i < so->map->height)
	{
		j = 0;
		while (j < so->map->weight)
		{
			printf("%i", so->map->arr[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
	
	return (true);
}

