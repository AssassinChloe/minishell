/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 12:22:40 by cassassi          #+#    #+#             */
/*   Updated: 2020/11/30 14:28:35 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*tmpdst;
	unsigned char	*tmpsrc;

	if (!(dst) && !(src))
		return (NULL);
	i = 0;
	tmpdst = (unsigned char *)dst;
	tmpsrc = (unsigned char *)src;
	while (i < n)
	{
		*(tmpdst + i) = *(tmpsrc + i);
		i++;
	}
	return (dst);
}
