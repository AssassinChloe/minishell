/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 13:27:14 by vmercier          #+#    #+#             */
/*   Updated: 2021/05/27 10:15:37 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (!src || !dest)
		return (0);
	else
	{
		while (src[count] != '\0')
			count++;
		if (dstsize == 0)
			return (count);
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
		return (count);
	}
}
