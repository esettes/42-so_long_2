/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:46:01 by rstancu           #+#    #+#             */
/*   Updated: 2026/01/16 15:53:14 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_line(char *line, size_t last_len, bool *same)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	if (line_len != last_len)
		*same = false;
}

ssize_t	check_lines_lenght(int32_t fd, t_solong *so)
{
	char	*line;
	size_t	last_len;
	ssize_t	lines;
	bool	same;

	lines = 0;
	same = true;
	line = get_next_line(fd);
	if (!line)
		return (lines);
	so->map->width = ft_strlen(line);
	if (line[so->map->width - 1] == '\n')
		so->map->width--;
	while (line)
	{
		lines++;
		last_len = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
		if (line)
			check_line(line, last_len, &same);
	}
	if (!same)
		return (-1);
	return (lines);
}

static bool	check_lines_and_malloc_arr(t_solong *so, char *file, ssize_t *lines)
{
	int32_t	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (free_all(so));
	*lines = check_lines_lenght(fd, so);
	close(fd);
	if (*lines < 1)
	{
		ft_putendl_fd("Error: Invalid map. \
Inconsistent line lengths/map needs NL at last line.", 2);
		return (false);
	}
	so->map->arr = malloc(sizeof(int32_t *) * (*lines));
	if (!so->map->arr)
	{
		free(so->map->arr);
		return (false);
	}
	return (true);
}

bool	check_map(t_solong *so, int fd)
{
	size_t	k;
	char	*line;

	k = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_valid_line(line) || !parse_line(so, line, k))
		{
			free(line);
			close(fd);
			free_map(so->map, so->mlx);
			return (false);
		}
		k++;
		free(line);
	}
	return (true);
}

bool	read_file(t_solong *so, char *file)
{
	ssize_t	lines;
	int32_t	fd;

	if (!check_lines_and_malloc_arr(so, file, &lines))
		return (false);
	fd = open(file, O_RDONLY);
	if (fd < 0 || !so->map->arr)
	{
		free_map(so->map, so->mlx);
		return (false);
	}
	if (!check_map(so, fd))
		return (false);
	close(fd);
	so->map->height = lines;
	if (!check_num_elemets(so))
	{
		free_map(so->map, so->mlx);
		return (false);
	}
	return (true);
}
