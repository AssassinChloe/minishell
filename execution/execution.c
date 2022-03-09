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
	if (is_valid_cmd(cmd) == 0)
	{
		printf("%s\n", cmd->av[0]);
		if (execve(cmd->av[0], cmd->av, /**(g_data.env_p)*/NULL) < 0)
				perror("minishell");
	}
	close(g_data.check);	
}

int	ft_child(int **pip, int i, t_cmd *cmd)
{
	char	*nb;

	if (i == g_data.nb_pipe)
		dup2(g_data.check, STDERR_FILENO);
	if (ft_divide_redirection(cmd) > 0)
	{
		ft_closepipe(pip);
		ft_endredir(cmd);
		close(g_data.check);
		g_data.exit_value = 1;
		return (0);
	}
	if (g_data.nb_pipe > 0)
	{
		if (i < g_data.nb_pipe)
			dup2(pip[i][1], STDOUT_FILENO);
		if (i > 0)
			dup2(pip[i - 1][0], STDIN_FILENO);
		ft_closepipe(pip);
		if (i == g_data.nb_pipe)
		dup2(g_data.check, STDERR_FILENO);
	}
	if (cmd->av[0] && cmd->type[0] == T_BUILTIN/*!ft_isbuiltin(cmd->av[0])*/)
	{
		launch_builtin(cmd);
		if (i == g_data.nb_pipe)
		{
		nb = ft_itoa(g_data.exit_value);
		write(2, nb, ft_strlen(nb));
		free(nb);
		}
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
		while (wait(NULL) != -1 || errno!= ECHILD)
			g_data.execution = 1;
		g_data.execution = 0;
	}
	close(g_data.check);
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
		ft_parent(pip);
	return (pid);
}

int	execute_command(t_list *commandlist)
{
	t_cmd	*command;
	int		**pip;
	int		pid;
	
	g_data.check = open(g_data.log, O_CREAT | O_RDWR | O_APPEND, 0666);
	if (g_data.check < 0)
		printf("error open\n");
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
