/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:40:39 by vmercier          #+#    #+#             */
/*   Updated: 2021/05/27 09:49:20 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	ch;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	ch = (unsigned char)c;
	while (i < n)
	{
		d[i] = s[i];
		if (s[i] == ch)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
