/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:02:00 by vmercier          #+#    #+#             */
/*   Updated: 2022/01/21 13:03:11 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_dollar(char *str)
{
	int	i;

	i = 0;
	if (!str)
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

char	*ft_extract_var(char *str)
	{
		int i;
		char	*tmp;
		char	*var;
		char	*conv;
	
		tmp = NULL;
		var = NULL;
		i = 0;
		while (str[i])
		{
			while (str[i] && str[i] != '$')
			{
				tmp = ft_strjoin_char(tmp, str[i]);
				i++;
			}
			if (str[i] == '$')
			{
				if (str[i + 1] == '?')
				{
					conv = getenv("?");
					tmp = ft_strjoin(tmp,ft_strdup(conv));
					i = i + 2;
				}
				else if (ft_isvarphabet(str[i + 1]) == 0)
				{
					tmp = ft_strjoin_char(tmp, str[i]);
					i++;
				}
				else
				{
					i++;
					while (ft_isvarphabet(str[i]) == 1)
					{
						var = ft_strjoin_char(var, str[i]);
						i++;
					}
					conv = getenv(var);
					free(var);
					tmp = ft_strjoin(tmp, ft_strdup(conv));
				}
				
			}
		}
		free(str);
		return (tmp);
	}

