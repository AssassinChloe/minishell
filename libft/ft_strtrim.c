/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:30:45 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/10 17:35:08 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarset(char c, char *set)
{
	int	j;

	j = 0;
	while (set[j])
	{
		if (set[j] == c)
			return (1);
		j++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*trim;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	if (!(s1))
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	k = 0;
	while (s1[i] && ft_ischarset(s1[i], (char *)set) == 1)
		i++;
	while (j > 0 && ft_ischarset(s1[j - 1], (char *)set) == 1)
		j--;
	if (i > j)
		trim = (char *)malloc(sizeof(char));
	else
		trim = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!(trim))
		return (NULL);
	while (i < j)
		trim[k++] = s1[i++];
	trim[k] = '\0';
	return (trim);
}
