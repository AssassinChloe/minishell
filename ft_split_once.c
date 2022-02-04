/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_once.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:26:53 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/01 15:27:10 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
//#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
*/

static char	**free_all(char **tmp)
{
	free((void *)tmp[0]);
	free((void *)tmp[1]);
	free(tmp);
	return (NULL);
}


char **ft_split_env(char *s)
{
	char **tmp;
	int i;
	int j;

	if (s == NULL)
		return (NULL);
	tmp = (char **)malloc(sizeof(char *) * 2);
	if (tmp == NULL)
		return(NULL);
	tmp[0] = (char *)malloc(sizeof(char)*ft_strlen(s));
	tmp[1] = (char *)malloc(sizeof(char)*ft_strlen(s));
	if (tmp[0] == NULL || tmp[1] == NULL)
		return (free_all((char **)tmp));
	i = 0;
	while (s[i] != '=')
	{
		tmp[0][i] = s[i];
		i++;
	}
	tmp[0][i++] = '\0';
	j = 0;
	while (s[i])
		tmp[1][j++] = s[i++];
	tmp[1][j] = '\0';
	return (tmp);
}
/*
int main()
{
	char *str="test=truc=chose";
	char **tmp;

	tmp = ft_split_env(str);
	printf("%s \n %s \n %s\n", str, tmp[0], tmp[1]);
	printf("long tmp[0] %i, long tmp[1] %i\n", (int)ft_strlen(tmp[0]), (int)ft_strlen(tmp[1]));
	free_all(tmp);
	return (0);
}
*/