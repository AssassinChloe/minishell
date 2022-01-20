/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:34:42 by vmercier          #+#    #+#             */
/*   Updated: 2021/05/25 16:32:18 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*str;

	if (s1 && s2)
	{
		size = ft_strlen(s1) + ft_strlen(s2);
		str = (char *)malloc(sizeof(char) * (size + 1));
		if (str == NULL)
			return (NULL);
		i = 0;
		j = -1;
		while (s1[++j])
			str[i++] = s1[j];
		j = -1;
		while (s2[++j])
			str[i++] = s2[j];
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
