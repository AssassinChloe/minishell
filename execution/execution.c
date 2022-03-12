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

void	exec_cmd(t_cmd *cmd)
{
	if (ft_strcmp(".heredoc", cmd->av[0]) == 0)
		close(g_data.check);
	else if (cmd->av[0] && is_valid_cmd(cmd) == 0)
	{
		if (execve(cmd->av[0], cmd->av, g_data.env_in_tab) < 0)
			perror("minishell");
		close(g_data.check);
	}
}

int	ft_child(int **pip, int i, t_cmd *cmd)
{
	if (i == g_data.nb_pipe)
		dup2(g_data.check, STDERR_FILENO);
	if (ft_divide_redirection(cmd) > 0)
	{
		ft_closepipe(pip);
		return (end_redir_error(cmd));
	}
	if (g_data.nb_pipe > 0)
		handle_pipe(i, pip);
	if (cmd->av[0] && cmd->type[0] == T_BUILTIN)
	{
		launch_builtin(cmd);
		get_exit_val_pipe(i);
		close(g_data.check);
	}
	else
		exec_cmd(cmd);
	if (cmd->redir_nb > 0)
		ft_endredir(cmd);
	return (0);
}

void	ft_parent(int **pip)
{	
	if (g_data.nb_pipe > 0)
		ft_closepipe(pip);
	g_data.execution = -1;
	while (g_data.execution == -1)
	{
		while (wait(NULL) != -1 || errno != ECHILD)
			g_data.execution = 1;
		g_data.execution = 0;
	}
	close(g_data.check);
}

int	ft_exec(t_list *commandlist, int **pip, int *i)
{
	int		pid;
	t_cmd	*command;

	pid = 1;
	command = (t_cmd *)commandlist->content;
	if (command->argc < 0)
		*i = *i + 1;
	else
		pid = fork();
	while (pid != 0 && (*i + 1) <= g_data.nb_pipe)
	{
		*i = *i +1;
		commandlist = commandlist->next;
		command = (t_cmd *)commandlist->content;
		if (command)
			pid = fork();
	}
	if (pid == 0)
		ft_child(pip, *i, command);
	else
		ft_parent(pip);
	return (pid);
}

int	execute_command(t_list *commandlist)
{
	t_cmd	*command;
	int		**pip;
	int		pid;
	int		i;

	i = 0;
	g_data.check = open(g_data.log, O_CREAT | O_RDWR | O_APPEND, 0666);
	pid = 1;
	command = (t_cmd *)commandlist->content;
	if (g_data.nb_pipe > 0)
	{
		pip = malloc(sizeof(int) * g_data.nb_pipe * 2);
		ft_open_pipes(pip);
	}
	if (g_data.nb_pipe == 0 && !ft_isbuiltin(command->av[0]))
		exec_builtin_nopipe(command);
	else
	{
		pid = ft_exec(commandlist, pip, &i);
		if (g_data.nb_pipe != 0)
			ft_free_pipe(pip);
	}
	close(g_data.check);
	return (pid);
}
