/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 09:59:52 by cassassi          #+#    #+#             */
/*   Updated: 2021/11/23 16:12:08 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char *str, char c)
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!newstr)
	{
		if (str)
			free(str);
		return (NULL);
	}
	if (str)
	{
		while (str[i])
		{
			newstr[i] = str[i];
			i++;
		}
		free(str);
	}
	newstr[i] = c;
	newstr[i + 1] = '\0';
	return (newstr);
}
