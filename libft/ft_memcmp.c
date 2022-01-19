/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:35:00 by cassassi          #+#    #+#             */
/*   Updated: 2020/11/20 15:36:24 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	int				diff;
	unsigned char	*tmps1;
	unsigned char	*tmps2;

	i = 0;
	diff = 0;
	tmps1 = (unsigned char *)s1;
	tmps2 = (unsigned char *)s2;
	while (i < n)
	{
		if (tmps1[i] != tmps2[i])
		{
			diff = (tmps1[i] - tmps2[i]);
			return (diff);
		}
		i++;
	}
	return (0);
}
