/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 11:59:41 by vmercier          #+#    #+#             */
/*   Updated: 2021/05/25 15:53:17 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;
	char	*str;

	i = 0;
	ch = (char)c;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == ch)
			return (str + i);
		i++;
	}
	if (str[i] == '\0' && ch == '\0')
		return (str + i);
	return (NULL);
}
