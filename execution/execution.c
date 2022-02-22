/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:27:03 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/14 09:40:29 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(char **cmd)
{
	if (execve(cmd[0], cmd, NULL) == -1)
		perror("minishell ");
}

int	ft_child(int **pip, int i, t_cmd *cmd)
{
	if (g_data.nb_pipe > 0)
		ft_closepipe(pip, i);
	if (g_data.nb_pipe > 0 && i < g_data.nb_pipe)
		dup2(pip[i][1], STDOUT_FILENO);
	if (g_data.nb_pipe > 0 && i > 0)
		dup2(pip[i - 1][0], STDIN_FILENO);
	ft_divide_redirection(cmd);
	if (!ft_isbuiltin(cmd->av[0]))
		launch_builtin(cmd);
	else
		exec_cmd(cmd->av);
	if (cmd->redir_nb > 0)
		ft_endredir(cmd);
	if (g_data.nb_pipe > 0)
		ft_closepipe_end(pip, i);
	return (0);
}

void	ft_parent(int **pip, int i)
{
if (g_data.nb_pipe > 0)
		ft_closepipe(pip, (i + 1));
	g_data.execution = -1;
	while (g_data.execution == -1)
	{
		g_data.execution = 1;
		while (wait(NULL) != -1 || errno != ECHILD)
		{
			g_data.execution = 0;
		}
	}
}

int	ft_exec(t_list *commandlist, int **pip)
{
	int		pid;
	t_cmd	*command;
	int		i;
	
	i = 0;
	command = (t_cmd *)commandlist->content;
	pid = fork();
	if (pid < 0)
		printf("error fork\n");
	while (pid != 0 && (i + 1) <= g_data.nb_pipe)
	{
		i++;
		commandlist = commandlist->next;
		command = (t_cmd *)commandlist->content;
		pid = fork();
	}
	if (pid == 0)
		ft_child(pip, i, command);
	else
		ft_parent(pip, i);
	return (pid);
}

int	execute_command(t_list *commandlist)
{
	
	t_cmd	*command;
	int		**pip;
	int		pid;

	pid = 1;
	command = (t_cmd *)commandlist->content;
	if (g_data.nb_pipe > 0)
	{
		pip = malloc(sizeof(int) * g_data.nb_pipe * 2);
		ft_open_pipes(pip);
	}
	if (g_data.nb_pipe == 0 && !ft_isbuiltin(command->av[0]))
	{
		ft_divide_redirection(command);
		launch_builtin(command);
		if (command->redir_nb > 0)
			ft_endredir(command);
	}
	else
	{
		pid = ft_exec(commandlist, pip);
		if (g_data.nb_pipe != 0)
			ft_free_pipe(pip);
	}
	return (pid);
}
