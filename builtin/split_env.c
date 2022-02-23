/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:19:21 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/23 17:19:25 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_tab2(char **tmp)
{
	free((void *)tmp[0]);
	free((void *)tmp[1]);
	free(tmp);
	return (NULL);
}

char	**ft_split_env(char *s)
{
	char	**tmp;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	tmp = (char **)malloc(sizeof(char *) * 2);
	if (tmp == NULL)
		return (NULL);
	tmp[0] = (char *)malloc(sizeof(char) * ft_strlen(s));
	tmp[1] = (char *)malloc(sizeof(char) * ft_strlen(s));
	if (tmp[0] == NULL || tmp[1] == NULL)
		return (free_tab2((char **)tmp));
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

char	**ft_split_env_plus(char *s)
{
	char	**tmp;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	tmp = (char **)malloc(sizeof(char *) * 2);
	if (tmp == NULL)
		return (NULL);
	tmp[0] = (char *)malloc(sizeof(char) * ft_strlen(s));
	tmp[1] = (char *)malloc(sizeof(char) * ft_strlen(s));
	if (tmp[0] == NULL || tmp[1] == NULL)
		return (free_tab2((char **)tmp));
	i = -1;
	while (s[++i] != '+')
		tmp[0][i] = s[i];
	tmp[0][i++] = '\0';
	i++;
	j = 0;
	while (s[i])
		tmp[1][j++] = s[i++];
	tmp[1][j] = '\0';
	return (tmp);
}
