/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:09:36 by vmercier          #+#    #+#             */
/*   Updated: 2021/06/04 11:44:38 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	w_len;
	int	count_w;

	i = 0;
	count_w = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		w_len = 0;
		while (s[i] && s[i] != c)
		{
			w_len++;
			i++;
		}
		if (w_len)
			count_w++;
	}
	return (count_w);
}

static int	numchar(char const *s2, char c, int i)
{
	int	lenght;

	lenght = 0;
	while (s2[i] != c && s2[i] != '\0')
	{
		lenght++;
		i++;
	}
	return (lenght);
}

static char	**free_all(char const **dst, int j)
{
	while (j > 0)
	{
		j--;
		free((void *)dst[j]);
	}
	free(dst);
	return (NULL);
}

static char	**affect(char const *s, char **dst, char c, int l)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < l)
	{
		k = 0;
		while (s[i] == c)
			i++;
		dst[j] = (char *)malloc(sizeof(char) * numchar(s, c, i) + 1);
		if (dst[j] == NULL)
			return (free_all((char const **)dst, j));
		while (s[i] != '\0' && s[i] != c)
			dst[j][k++] = s[i++];
		dst[j][k] = '\0';
		j++;
	}
	dst[j] = 0;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		nb_words;

	if (s == NULL)
		return (NULL);
	nb_words = count_words(s, c);
	dst = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (dst == NULL)
		return (NULL);
	return (affect(s, dst, c, nb_words));
}
