/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:27:03 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/13 23:30:01 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(char **cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, NULL) == -1)
			perror("shell");
	}
}

void	execute_command(t_list *commandlist)
{
	t_cmd *command;

	command = (t_cmd *)commandlist->content;
	if (g_data.nb_pipe == 0)
    {
		
		ft_divide_redirection(commandlist);
		ft_get_cmd_path(command);
		if (command->redir_nb > 0)
			ft_endredir(command);
	    return ;
    }
	else
	{
		ft_pipe(commandlist);
	}
	
}
