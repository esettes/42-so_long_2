/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-14 14:20:41 by rstancu           #+#    #+#             */
/*   Updated: 2025-11-14 14:20:41 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

void	print_movements(t_solong *so)
{
	char	*num_str;

	printf("last pos: (%d, %d)\n", so->player.last_pos.x, so->player.last_pos.y);
	printf("current pos: (%d, %d)\n", (int32_t)(so->player.pos.x / TILESIZE), (int32_t)(so->player.pos.y / TILESIZE));
	if (so->player.last_pos.x == (int32_t)(so->player.pos.x / TILESIZE)
		&& so->player.last_pos.y == (int32_t)(so->player.pos.y / TILESIZE))
		return ;
	else
	{
		so->movements_count++;
	}
	if (so->movements_img)
		mlx_delete_image(so->mlx, so->movements_img);
	num_str = ft_itoa(so->movements_count);
	if (!num_str)
		return ;
	so->movements_img = mlx_put_string(so->mlx, num_str, 10, 10);
	free(num_str);
}