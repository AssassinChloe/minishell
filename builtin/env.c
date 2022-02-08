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

int	ft_env(t_cmd cmd)
{
	t_env	*var;

	if (cmd.argc != 1)
	{
		ft_putstr_fd("env : ", STDOUT_FILENO);
		ft_putstr_fd(cmd.argv[1], STDOUT_FILENO);
		ft_putendl_fd(": No such file or directory", STDOUT_FILENO);
		g_data.exit_value = 127;
	}
	var = g_data.env;
	while (var)
	{
		ft_putstr_fd(var->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putendl_fd(var->value, STDOUT_FILENO);
		var = var->next;
	}
	return (0);
}
