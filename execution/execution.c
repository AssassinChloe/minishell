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

void	sigusr_handler(int sig)
{
	if (sig == SIGUSR1)
		g_data.test = 0;	
}

int	ft_child(int **pip, int i, t_cmd *cmd)
{
	ft_divide_redirection(cmd);
	if (g_data.nb_pipe > 0)
	{
		ft_closepipe(pip, i);
		if (i < g_data.nb_pipe)
			dup2(pip[i][1], STDOUT_FILENO);
		if (i > 0)
			dup2(pip[i - 1][0], STDIN_FILENO);
		if_redir(pip, cmd, i);
	}
	if (!ft_isbuiltin(cmd->av[0]))
		launch_builtin(cmd);
	else
		exec_cmd(cmd->av);
	if (g_data.nb_pipe > 0)
		ft_closepipe_end(pip, i);
	if (cmd->redir_nb > 0)
		ft_endredir(cmd);
	return (0);
}

void	ft_parent(int **pip, int i, int *pid_tab)
{
	int	j;
	int status;

	j = 0;
	if (g_data.nb_pipe > 0)
		ft_closepipe(pip, (i + 1));
	while (j < g_data.nb_pipe + 1)
	{
		g_data.execution = 1;
		kill(pid_tab[j], SIGUSR1);
		waitpid(pid_tab[j], &status, 0);
		j++;
	}
	g_data.execution = 0;
}

int	ft_exec(t_list *commandlist, int **pip)
{
	int		pid;
	int		*pid_tab;
	t_cmd	*command;
	int		i;
	struct sigaction sig;

	g_data.test = 1;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sig.sa_handler = sigusr_handler;
	i = 0;
	pid_tab = malloc(sizeof(int) * (g_data.nb_pipe + 1));
	command = (t_cmd *)commandlist->content;
	pid = fork();
	pid_tab[i] = pid;
	if (pid < 0)
		printf("error fork\n");
	while (pid != 0 && (i + 1) <= g_data.nb_pipe)
	{
		i++;
		commandlist = commandlist->next;
		command = (t_cmd *)commandlist->content;
		pid = fork();
		pid_tab[i] = pid;
	}
	if (pid == 0)
	{
		while (g_data.test == 1) 
			sigaction(SIGUSR1, &sig, NULL);
		ft_child(pip, i, command);
	}
	else
		ft_parent(pip, i, pid_tab);
	free(pid_tab);
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
