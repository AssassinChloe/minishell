/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 11:00:53 by cassassi          #+#    #+#             */
/*   Updated: 2020/11/19 11:28:43 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*swp;

	i = 0;
	swp = (unsigned char *)b;
	while (i < len)
	{
		swp[i] = (unsigned char)c;
		i++;
	}
	b = (void *)swp;
	return (b);
}
