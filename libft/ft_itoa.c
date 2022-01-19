/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 10:44:42 by cassassi          #+#    #+#             */
/*   Updated: 2021/06/10 12:38:38 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int				len;
	unsigned int	nb;

	if (n < 0)
	{
		nb = -n;
		len = 2;
	}
	else
	{
		nb = n;
		len = 1;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*trad;
	int				len;
	unsigned int	nb;

	len = ft_len(n);
	trad = (char *)malloc(sizeof(char) * len + 1);
	if (!(trad))
		return (NULL);
	trad[len] = '\0';
	len--;
	if (n < 0)
		nb = -n;
	else
		nb = n;
	trad[len] = (nb % 10) + '0';
	len--;
	while (nb >= 10)
	{
		nb = nb / 10;
		trad[len] = (nb % 10) + '0';
		len--;
	}
	if (n < 0)
		trad[0] = '-';
	return (trad);
}
