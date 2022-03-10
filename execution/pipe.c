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

void	ft_closepipe(int **pip)
{
	int	j;

	j = 0;
	while (j < g_data.nb_pipe)
	{
		if (close(pip[j][0]) < 0)
			printf("error close\n");
		if (close(pip[j][1]) < 0)
			printf("error close\n");
		j++;
	}
}

/*void if_redir(int **pip, t_cmd *cmd, int i)
{
	int	j;
	int	tab_type[4];

	j = 0;
	while (j < 4)
		tab_type[j++] = 0;
	j = 0;
	if (cmd->redir_nb > 0)
	{
		while (j < cmd->redir_nb)
		{
			if (cmd->redir[j].type == T_LOWER)
				tab_type[0] = 1;
			if (cmd->redir[j].type == T_GREATER)
				tab_type[1] = 1;
			if (cmd->redir[j].type == T_LLOWER)
				tab_type[2] = 1;
			if (cmd->redir[j].type == T_GGREATER)
				tab_type[3] = 1;
			j++;
		}
	}
	if (tab_type[0] == 1 || tab_type[2] == 1)
	{
		if (i < g_data.nb_pipe)
		close(pip[i][1]);
	}
	if (tab_type[1] == 1 || tab_type[3] == 1)
	{
		if (i > 0)
			close(pip[i - 1][0]);
	}
	if (cmd->redir_nb > 0)
	{
		if (i < g_data.nb_pipe && tab_type[2] == 0 && tab_type[0] == 0)
			dup2(pip[i][1], STDOUT_FILENO);
		if (i > 0 && tab_type[1] == 0 && tab_type[3] == 0)
			dup2(pip[i - 1][0], STDIN_FILENO);
	}
	else
	{
		if (i < g_data.nb_pipe)
			dup2(pip[i][1], STDOUT_FILENO);
		if (i > 0)
			dup2(pip[i - 1][0], STDIN_FILENO);
	}
}*/