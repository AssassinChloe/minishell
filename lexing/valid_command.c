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

void	ft_error_check_cmd(t_cmd *cmd, int *ret)
{
	if (cmd->env == 0)
	{
		if (*ret == 126)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->av[0], STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
//			g_data.exit_value = 126;
		}
//			printf("minishell: %s: Is a directory\n", cmd->av[0]);
		else if (*ret == 127)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->av[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
//			g_data.exit_value = 127;
		}
//			printf("minishell: %s: command not found\n", cmd->av[0]);
	}
	else
	{
		if (*ret > 0)
		{
			ft_putstr_fd("env: ", STDERR_FILENO);
			ft_putstr_fd(cmd->av[0], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
//			g_data.exit_value = 127;
//			printf("env: %s: No such file or directory\n", cmd->av[0]);
			*ret = 127;
		}
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
			*trunc_type[j] = get_token_type(cmd->av[i], &multicmd);
		*trunc_list[j++] = ft_strdup(cmd->av[i++]);
	}
	trunc_list[j] = NULL;
	return (i);
}

void	ft_check_for_env(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**trunc_list;
	int		*trunc_type;

	i = 0;
	j = 0;
	while (cmd->av[i] && ft_strcmp(cmd->av[i], "env") == 0)
			i++;
	if (i > 0 && i < cmd->argc)
	{
		cmd->env = 1;
		trunc_list = malloc(sizeof(char *) * (cmd->argc - i + 1));
		trunc_type = malloc(sizeof(int) * (cmd->argc - i));
		i = copy_cmdlist(cmd, &trunc_list, &trunc_type, i);
		free_t_cmd(i, cmd);
		cmd->av = trunc_list;
		cmd->type = trunc_type;
		while (cmd->av[j])
			j++;
		cmd->argc = j;
		cmd->argc_init = j;
	}
	else
		cmd->env = 0;
}

int	is_valid_cmd(t_cmd *cmd)
{
	struct stat	*test;
	int			ret;
	int			i;

	ret = 0;
	i = 0;
	ft_check_for_env(cmd);
	test = malloc(sizeof(struct stat));
	while (cmd->av[i] && cmd->type[i] != T_BUILTIN && cmd->type[i] != T_CMD)
		i++;
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
