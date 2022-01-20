/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 12:10:26 by vmercier          #+#    #+#             */
/*   Updated: 2021/05/25 15:49:06 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_size(int n)
{
	int		count;
	long	res;

	res = n;
	count = 1;
	if (res < 0)
	{
		count++;
		res *= (-1);
	}
	while (res >= 10)
	{
		count++;
		res /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	res;
	int		i;
	int		len;

	i = 0;
	len = check_size(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	res = n;
	if (res < 0)
		res *= -1;
	str[len - i++] = '\0';
	while (res >= 10)
	{
		str[len - i++] = (res % 10) + '0';
		res /= 10;
	}
	str[len - i++] = (res % 10) + '0';
	return (str);
}
