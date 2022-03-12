/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:50:32 by cassassi          #+#    #+#             */
/*   Updated: 2022/03/02 23:50:36 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_check_cmd(t_cmd *cmd, int ret)
{
	if (ret == 126)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->av[0], STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	}
	else if (ret == 127)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->av[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
}

void	free_t_cmd(int i, t_cmd *cmd)
{
	while (i >= 0)
	{
		free(cmd->av[i]);
		cmd->av[i] = NULL;
		i--;
	}
	free(cmd->av);
	free(cmd->type);
}

int	copy_cmdlist(t_cmd *cmd, char ***trunc_list, int **trunc_type, int i)
{
	int	multicmd;
	int	j;

	j = 0;
	multicmd = 0;
	while (i < cmd->argc)
	{
		if (j > 0 && (cmd->type[j - 1] >= T_LOWER
				&& cmd->type[j - 1] <= T_GGREATER))
			*trunc_type[j] = T_FILENAME;
		else
			*trunc_type[j] = get_type(cmd->av[i], &multicmd);
		*trunc_list[j++] = ft_strdup(cmd->av[i++]);
	}
	trunc_list[j] = NULL;
	return (i);
}

int	is_valid_cmd(t_cmd *cmd)
{
	struct stat	*test;
	int			i;

	i = 0;
	test = malloc(sizeof(struct stat));
	if (cmd->av[0] && (cmd->type[0] >= T_LOWER && cmd->type[0] <= T_GGREATER))
	{
		while (cmd->av[i] && cmd->type[i] != T_BUILTIN && cmd->type[i] != T_CMD)
			i++;
	}
	if (i < cmd->argc && cmd->av[i] && stat(cmd->av[i], test) >= 0
		&& S_ISDIR(test->st_mode) == 1)
	{	
		free(test);
		test = NULL;
		return (126);
	}
	free(test);
	test = NULL;
	if (i < cmd->argc && (ft_strcmp(cmd->av[i], "") == 0
			|| (cmd->type[i] != T_BUILTIN && ft_get_cmd_path(&cmd->av[i]) > 0)))
		return (127);
	return (0);
}
