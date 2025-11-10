/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-02 14:34:21 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-02 14:34:21 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_chars(const char *str, int *is_neg)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		sign++;
		if (str[i] == '-')
			*is_neg = 1;
		i++;
	}
	if (sign > 1)
		return (-1);
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	res;
	int			is_neg;

	i = 0;
	res = 0;
	is_neg = 0;
	i = check_chars(str, &is_neg);
	if (i == -1)
		return (0);
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (is_neg)
		res *= -1;
	return ((int)res);
}

// int main()
// {
// 	const char *str = "+\t\v\f\r\n \f1234";
// 	int result = ft_atoi(str);
// 	printf("my result: %d\natoi result: %d \n", result, atoi(str));
// 	return 0;
// }
