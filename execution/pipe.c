/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:28:00 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/14 10:37:05 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child(int **pip, int i, t_list *cmdlist, t_cmd *cmd)
{
	ft_closepipe(pip, i);
	ft_divide_redirection(cmdlist);
	if (i < g_data.nb_pipe)
		dup2(pip[i][1], STDOUT_FILENO);
	if (i > 0)
		dup2(pip[i - 1][0], STDIN_FILENO);
	ft_get_cmd_path(cmd);
	if (cmd->redir_nb > 0)
		ft_endredir(cmd);
	ft_closepipe_end(pip, i);
	exit(EXIT_SUCCESS);
}

void	ft_parent(int **pip, int i)
{
	int	x;

	ft_closepipe(pip, (i + 1));
	x = 0;
	while (x == 0)
	{
		x = -1;
		while (wait(NULL) != -1 || errno != ECHILD)
			x = 0;
	}
}

void	ft_free_pipe(int **pip)
{
	int	i;

	i = 0;
	while (i < g_data.nb_pipe)
	{
		free(pip[i]);
		i++;
	}
	free(pip);
}

void	ft_open_pipes(int **pip)
{
	int	i;

	i = 0;
	while (i < g_data.nb_pipe)
	{
		pip[i] = malloc(sizeof(int) * 2);
		if (pipe(pip[i]) < 0)
			printf("error pipe\n");
		i++;
	}
}

void	ft_pipe(t_list *commandlist)
{
	int		pid;
	t_cmd	*command;
	int		**pip;
	int		i;

	i = 0;
	pip = malloc(sizeof(int) * g_data.nb_pipe * 2);
	command = (t_cmd *)commandlist->content;
	ft_open_pipes(pip);
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
		ft_child(pip, i, commandlist, command);
	else
		ft_parent(pip, i);
	ft_free_pipe(pip);
	return ;
}
