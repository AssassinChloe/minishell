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

void	ft_extract_var(t_list **tokens, char *str)
	{
		int i;
		char *tmp;
		int	number;

		tmp = NULL;
		tmp = ft_strjoin_char(tmp, '"');
		i = 1;
		number = 0;
		while (str[i] != '"')
		{
			while(str[i] != '"' && str[i] != '$')
			{
				tmp = ft_strjoin_char(tmp, str[i]);
				i++;
			}
			if (str[i] == '$')
			{
				if (str[i + 1] == '"' || ft_isspace(str[i + 1]) == 1)
				{
					tmp = ft_strjoin_char(tmp, str[i]);
					i++;
				}
				else
				{
					ft_addone(tokens, &tmp);
					tmp = ft_strjoin_char(tmp, str[i]);
					i++;
					if (ft_isdigit(str[i]) == 1 || str[i] == '$')
					{
						tmp = ft_strjoin_char(tmp, str[i]);
						ft_addone(tokens, &tmp);
						i++;
					}
					else
					{
						while (str[i] !='"' && ft_isspace(str[i]) == 0
						&& ft_isalnum(str[i]) == 1 && number == 0)
						{
							tmp = ft_strjoin_char(tmp, str[i]);
							if (ft_isdigit(str[i]) == 1)
								number = 1;
							i++;
						}
						ft_addone(tokens, &tmp);
					}
				}
				
			}
		}
		tmp = ft_strjoin_char(tmp, str[i]);
		ft_addone(tokens, &tmp);
	}
