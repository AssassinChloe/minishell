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

int	launch__builtin(t_cmd cmd)
{
	if (ft_strcmp(cmd.argv[0], "cd") == 0)
		return (ft_cd(cmd));
	if (ft_strcmp(cmd.argv[0], "echo") == 0)
		return (ft_echo(cmd.argv));
	if (ft_strcmp(cmd.argv[0], "env") == 0)
		return (ft_env(cmd));
	if (ft_strcmp(cmd.argv[0], "exit") == 0)
		return (ft_exit(cmd));
//	if (ft_strcmp(cmd.argv[0], "export") == 0)
//		return (ft_export(cmd));
	if (ft_strcmp(cmd.argv[0], "pwd") == 0)
		return (ft_pwd());
//	if (ft_strcmp(cmd->argv[0], "unset") == 0)
//		return (ft_unset(cmd->argv));
	return (1);
}
