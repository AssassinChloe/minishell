/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:36:10 by cassassi          #+#    #+#             */
/*   Updated: 2020/11/20 11:56:57 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmps;
	unsigned char	tmpc;

	i = 0;
	tmps = (unsigned char *)s;
	tmpc = (unsigned char)c;
	while (i < n)
	{
		if (tmps[i] == tmpc)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
