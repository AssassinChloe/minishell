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
		perror("shell");
}

void	execute_command(t_list *commandlist)
{
	int		pid;
	t_cmd	*command;
	int		**pip;
	int		i;

	i = 0;
	command = (t_cmd *)commandlist->content;
	if (g_data.nb_pipe != 0)
	{
		pip = malloc(sizeof(int) * g_data.nb_pipe * 2);
		ft_open_pipes(pip);
	}
	if (g_data.nb_pipe == 0 && !ft_isbuiltin(command->av[0]))
		launch_builtin(command);
	else
	{
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
		if (g_data.nb_pipe != 0)
			ft_free_pipe(pip);
	}
	return ;
}
