/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:22:57 by vmercier          #+#    #+#             */
/*   Updated: 2021/05/25 15:45:34 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\v'
		|| ch == '\r' || ch == '\n' || ch == '\f')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	long long int	res;

	i = 0;
	res = 0;
	sign = 1;
	while (check(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return ((int)(res * sign));
}
