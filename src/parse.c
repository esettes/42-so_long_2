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

bool	is_map_valid_char(char c)
{
	return (c == M_WALL || c == M_SPACE || c == M_PLAYER
		|| c == M_EXIT || c == M_COLLECTIBLE);
}

bool	is_valid_extension(const char *file)
{
	size_t		len;
	size_t		ext_len;
	const char	*ext = ".ber";

	if (!file)
		return (false);
	len = ft_strlen(file);
	ext_len = ft_strlen(ext);
	if (len < ext_len)
		return (false);
	return (ft_strncmp((char *)file + len - ext_len,
			(char *)ext, ext_len) == 0);
}
