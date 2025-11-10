/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-03 10:40:43 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-03 10:40:43 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
		return (0);
	return (1);
}

// int main()
// {
// 	int test_char = 'a';
// 	if (ft_isalpha(test_char))
// 		printf("%c is an alphabetic character.\n", test_char);
// 	else
// 		printf("%c is not an alphabetic character.\n", test_char);
// 	return 0;
// }