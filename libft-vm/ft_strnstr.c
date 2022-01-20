/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:33:42 by vmercier          #+#    #+#             */
/*   Updated: 2021/05/27 09:56:27 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dest;
	char	*src;

	i = 0;
	dest = (char *)big;
	src = (char *)little;
	if (*src == '\0' || src == NULL)
		return (dest);
	while (dest[i] && i < len)
	{
		j = 0;
		while (src[j] == dest[i + j] && i + j < len)
		{
			if (src[j + 1] == '\0')
				return (&dest[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
