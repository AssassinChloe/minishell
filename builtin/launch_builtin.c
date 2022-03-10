/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:47:26 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/01 14:47:38 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_builtin(t_cmd *cmd)
{
	close(g_data.check);
	if (ft_strcmp(cmd->av[0], "cd") == 0)
		g_data.exit_value = (ft_cd(*cmd));
	if (ft_strcmp(cmd->av[0], "echo") == 0)
		g_data.exit_value = ft_echo((*cmd).av);
	if (ft_strcmp(cmd->av[0], "env") == 0)
	{
		g_data.exit_value = ft_env();
		g_data.env_in_tab = ft_env_in_tab();
	}
	if (ft_strcmp(cmd->av[0], "exit") == 0)
		g_data.exit_value = ft_exit(*cmd);
	if (ft_strcmp(cmd->av[0], "export") == 0)
	{
		g_data.exit_value = ft_export(*cmd);
		g_data.env_in_tab = ft_env_in_tab();
	}	
	if (ft_strcmp(cmd->av[0], "pwd") == 0)
		g_data.exit_value = ft_pwd(*cmd);
	if (ft_strcmp(cmd->av[0], "unset") == 0)
	{
		g_data.exit_value = ft_unset((*cmd).av);
		g_data.env_in_tab = ft_env_in_tab();
	}
	return (g_data.exit_value);
}
