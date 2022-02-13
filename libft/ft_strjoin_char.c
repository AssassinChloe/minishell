/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 09:59:52 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/13 22:52:30 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_copy(char *newstr, char *str, int *i)
{
	while (str[*i])
	{
		newstr[*i] = str[*i];
		*i = *i + 1;
	}
}

char	*ft_strjoin_char(char *str, char c)
{
	char	*newstr;
	int		i;

	i = 0;
	if (str != NULL)
		newstr = malloc(sizeof(char) * (ft_strlen(str) + 2));
	else
		newstr = malloc(sizeof(char) * 2);
	if (!newstr)
	{
		if (str != NULL)
			free(str);
		return (NULL);
	}
	if (str != NULL)
	{
		ft_copy(newstr, str, &i);
		free(str);
	}
	newstr[i] = c;
	newstr[i + 1] = '\0';
	return (newstr);
}
