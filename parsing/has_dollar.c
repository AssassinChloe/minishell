/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:02:00 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/13 19:39:47 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_dollar(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_isvarphabet(char c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

void	ft_extract_exitval(char **tmp, int *i)
{
	char	*conv;

	conv = ft_itoa(g_data.exit_value);
	*tmp = ft_strjoin(*tmp, ft_strdup(conv));
	free(conv);
	*i = *i + 2;
}

void	ft_copyvarvalue(char **tmp, char *str, int *i)
{
	char	*var;
	char	*conv;

	var = NULL;
	*i = *i + 1;
	while (str[*i] && ft_isvarphabet(str[*i]) == 1)
	{
		var = ft_strjoin_char(var, str[*i]);
		*i = *i + 1;
	}
	conv = get_env_value(var);
	free(var);
	var = NULL;
	*tmp = ft_strjoin(*tmp, conv);
	free(conv);
	conv = NULL;
}

char	*ft_extract_var(char *str)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			tmp = ft_strjoin_char(tmp, str[i++]);
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				ft_extract_exitval(&tmp, &i);
			else if (ft_isvarphabet(str[i + 1]) == 0)
			{
				if (ft_isspace(str[i + 1]) == 1 || str[i + 1] == '\0'
				|| str[i + 1] == ':' || str[i + 1] == '=')
					tmp = ft_strjoin_char(tmp, str[i]);
				i++;
			}
			else
				ft_copyvarvalue(&tmp, str, &i);
		}
	}
	free(str);
	return (tmp);
}
