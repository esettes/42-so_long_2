/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstancu <rstancu@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-01 10:40:00 by rstancu           #+#    #+#             */
/*   Updated: 2025-10-01 10:40:00 by rstancu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while (n--)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}

/**
 * 1u enssures unsigned 1
 * (b & (1u << k)) creates mask to check if a bit of b is activated or not
 */
// static void char_to_bits8(unsigned char src, char out[10], int sep)
// {
//     int 			j = 0;
//     int				k = 7;
// 	unsigned int	mask;
// 	int				bit_one;

// 	while (k >= 0)
// 	{
// 		mask = (1u << k);
// 		bit_one = (src & mask) != 0;
// 		if (bit_one)
// 			out[j] = '1';
// 		else
// 			out[j] = '0';
// 		j++;
// 		if (sep && k == 4)
// 		{
// 			out[j] = ' ';
// 			j++;
// 		}
// 		k--;
// 	}
//     out[j] = '\0';
// }

// int	ft_memcmp_bits(const void *s1, const void *s2, size_t n)
// {
// 	const unsigned char	*str1;
// 	const unsigned char	*str2;
// 	unsigned char		aux1, aux2;
// 	char		bs1[10], bs2[10];
// 	size_t i = 0;

// 	str1 = (const unsigned char *)s1;
// 	str2 = (const unsigned char *)s2;
// 	while (i < n)
// 	{
// 		if (*str1 != *str2)
// 		{
// 			aux1 = *str1;
// 			aux2 = *str2;
// 			char_to_bits8(aux1, bs1, 1);
// 			char_to_bits8(aux2, bs2, 1);
// 			printf("%c = %s\n%c = %s\n", aux1, bs1, aux2, bs2);
// 			return (*str1 - *str2);
// 		}
// 		str1++;
// 		str2++;
// 		i++;
// 	}
// 	return (0);
// }

// int main(void)
// {
//     unsigned char x[] = "hello";
//     unsigned char y[] = "hellp";
//     int r = ft_memcmp_bits(x, y, sizeof(x));
//     printf("return: %d\n", r);
//     return 0;
// }
