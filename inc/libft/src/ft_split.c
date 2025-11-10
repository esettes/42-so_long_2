/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:36:44 by rstancu           #+#    #+#             */
/*   Updated: 2025/10/03 10:13:10 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_memory(void **arr, size_t pos)
{
	while (pos--)
		free (arr[pos]);
	free(arr);
	return (NULL);
}

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	size_t	check;
	char	*a;

	words = 0;
	check = 0;
	a = (char *)s;
	while (*a)
	{
		if (*a != c && check == 0)
		{
			words++;
			check = 1;
		}
		if (*a == c)
			check = 0;
		a++;
	}
	return (words);
}

static void	*set_pos(char const *s, size_t start, size_t end)
{
	size_t	j;
	char	*str;
	char	*b;

	j = 0;
	str = malloc(sizeof(char) * (end - start + 1));
	b = (char *)s;
	if (!str)
		return (NULL);
	while (start < end)
		str[j++] = b[start++];
	str[j] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	start;
	size_t	pos;

	i = -1;
	pos = 0;
	arr = malloc(sizeof(char *) * ((count_words(s, c)) + 1));
	if (!arr)
		return (NULL);
	while (++i < ft_strlen(s) && pos < count_words(s, c))
	{
		if (*(s + i) != c)
		{
			start = i;
			while (i < ft_strlen(s) && *(s + i) != c)
				i++;
			arr[pos++] = set_pos(s, start, i);
			if (arr[pos - 1] == NULL)
				return (free_memory((void **)arr, pos));
		}
	}
	arr[pos] = 0;
	return (arr);
}

__attribute__((weak))
int	main(int ac, char **av)
{
	char	**tab;
	int		i;

	(void)ac;
	tab = ft_split(av[1], av[2][0]);
	i = 0;
	while (tab[i])
	{
		i++;
	}
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (0);
}
