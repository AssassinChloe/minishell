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
	tmp = ft_itoa(num);
//	printf("SHLVL VALUE = %s\n", tmp);
	change_env_value("SHLVL", ft_strdup(tmp), 1);
//	search_var("SHLVL")->value = ft_strdup(tmp);
	free(tmp);
}

int	ft_env(t_cmd cmd)
{
	t_env	*var;

	if (cmd.argc != 1)
	{
		ft_putstr_fd("env : ", STDOUT_FILENO);
		ft_putstr_fd(cmd.av[1], STDOUT_FILENO);
		ft_putendl_fd(": No such file or directory", STDOUT_FILENO);
		g_data.exit_value = 127;
	}
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
