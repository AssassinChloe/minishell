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

void	ft_extract_exitval(char **tmp, int *i)
{
	char	*conv;

	conv = ft_itoa(g_data.exit_value);
	*tmp = ft_strjoin(*tmp, conv);
	free(conv);
	conv = NULL;
	*i = *i + 2;
}

void	ft_copyvarvalue(char **tmp, char *str, int *i, int quote)
{
	char	*var;
	char	*conv;

	var = NULL;
	*i = *i + 1;
	if (quote == 0)
		build_split_list(str);
	while (str[*i] && ft_isvarphabet(str[*i]) == 1)
	{
		var = ft_strjoin_char(var, str[*i]);
		*i = *i + 1;
	}
	conv = get_env_value(var);
	free(var);
	var = NULL;
	if (conv)
	{
		*tmp = ft_strjoin(*tmp, conv);
		free(conv);
		conv = NULL;
	}
}

void	handle_spechar_next_dollar(int *i, char *str, char **tmp)
{
	if (ft_isspace(str[*i + 1]) == 1 || str[*i + 1] == '\0'
		|| str[*i + 1] == ':' || str[*i + 1] == '=')
		*tmp = ft_strjoin_char(*tmp, str[*i]);
	*i = *i + 1;
}

char	*ft_extract(char *str, int quote, int start)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (str[i] && i < start)
		tmp = ft_strjoin_char(tmp, str[i++]);
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			tmp = ft_strjoin_char(tmp, str[i++]);
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				ft_extract_exitval(&tmp, &i);
			else if (ft_isvarphabet(str[i + 1]) == 0)
				handle_spechar_next_dollar(&i, str, &tmp);
			else
				ft_copyvarvalue(&tmp, str, &i, quote);
		}
	}
	free(str);
	return (tmp);
}
