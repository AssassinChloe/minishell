/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 10:30:34 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/01 10:31:45 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_shlvl_value(void)
{
	char	*tmp;
	int		num;

	tmp = get_env_value("SHLVL");
	num = ft_atoi(tmp);
	num++;
	free(tmp);
	tmp = NULL;
	tmp = ft_itoa(num);
	change_env_value("SHLVL", ft_strdup(tmp), 1);
	free(tmp);
}

int	ft_env(t_cmd cmd)
{
	t_env	*var;

	(void)cmd;
	var = g_data.env;
	while (var)
	{
		if (var->has_value)
		{
			ft_putstr_fd(var->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(var->value, STDOUT_FILENO);
		}
		var = var->next;
	}
	return (0);
}
