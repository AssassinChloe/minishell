/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:13:16 by vmercier          #+#    #+#             */
/*   Updated: 2021/05/25 16:38:13 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;
	char	*str;
	char	*ret;

	i = 0;
	ch = (char)c;
	str = (char *)s;
	ret = NULL;
	if (ch == '\0')
		return (str + ft_strlen(s));
	while (str[i])
	{
		if (str[i] == ch)
			ret = &str[i];
		i++;
	}
	return (ret);
}
