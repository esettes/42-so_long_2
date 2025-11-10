/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-01 10:36:35 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-01 10:36:35 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_digits(int n)
{
	int	i;

	i = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	num;
	int		count;
	int		i;
	char	*ret;

	num = (long)n;
	count = get_num_digits(num);
	if (num < 0)
	{
		num *= -1;
		count++;
	}
	ret = malloc(sizeof(char) * count + 1);
	if (!ret)
		return (NULL);
	i = count - 1;
	while (i >= 0)
	{
		ret[i--] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		ret[0] = '-';
	ret[count] = '\0';
	return (ret);
}

// int main()
// {
// 	printf("%s\n", ft_itoa(-9998));
// 	return (0);
// }