/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:23:56 by cassassi          #+#    #+#             */
/*   Updated: 2020/11/19 15:30:59 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*tmpdst;
	unsigned char	*tmpsrc;
	unsigned char	tmpc;

	i = 0;
	tmpdst = (unsigned char *)dst;
	tmpsrc = (unsigned char *)src;
	tmpc = (unsigned char)c;
	while (i < n)
	{
		tmpdst[i] = tmpsrc[i];
		if (tmpsrc[i] == tmpc)
		{
			return ((void *)&tmpdst[i + 1]);
		}
		i++;
	}
	return (NULL);
}
