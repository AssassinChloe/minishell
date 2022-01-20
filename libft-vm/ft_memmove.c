/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:59:40 by vmercier          #+#    #+#             */
/*   Updated: 2021/05/25 15:52:18 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t len)
{
	unsigned char	*dest;
	unsigned char	*src;
	size_t			i;

	dest = (unsigned char *)destination;
	src = (unsigned char *)source;
	if (dest == src)
		return (destination);
	i = 0;
	if (dest > src)
	{
		while (++i <= len)
			dest[len - i] = src[len - i];
	}
	else
	{
		while (i < len)
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (destination);
}
