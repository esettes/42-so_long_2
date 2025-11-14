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

	if (so->movements_img)
		mlx_delete_image(so->mlx, so->movements_img);
	num_str = ft_itoa(so->movements_count);
	if (!num_str)
		return ;
	so->movements_img = mlx_put_string(so->mlx, num_str, 10, 10);
	free(num_str);
}