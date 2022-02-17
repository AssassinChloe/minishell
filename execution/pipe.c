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

void	ft_child(int **pip, int i, t_cmd *cmd)
{
	printf("passe par child\n");
	if (g_data.nb_pipe > 0)
		ft_closepipe(pip, i);
	ft_divide_redirection(cmd);
	if (g_data.nb_pipe > 0 && i < g_data.nb_pipe)
		dup2(pip[i][1], STDOUT_FILENO);
	if (g_data.nb_pipe > 0 && i > 0)
		dup2(pip[i - 1][0], STDIN_FILENO);
	if (!ft_isbuiltin(cmd->av[0]))
		launch_builtin(cmd);
	else
		ft_get_cmd_path(cmd);
	if (cmd->redir_nb > 0)
		ft_endredir(cmd);
	if (g_data.nb_pipe > 0)
		ft_closepipe_end(pip, i);
	exit(EXIT_SUCCESS);
}

void	ft_parent(int **pip, int i)
{
	if (g_data.nb_pipe > 0)
		ft_closepipe(pip, (i + 1));
	g_data.execution = 1;
	while (g_data.execution == 1)
	{
		g_data.execution = 0;
		while (wait(NULL) != -1 || errno != ECHILD)
			g_data.execution = 1;
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
