/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 21:59:22 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/13 22:03:42 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_divide_redirection(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_countredir(cmd);
	if (cmd->redir_nb > 0)
	{
		cmd->redir = malloc(sizeof(t_redir) * cmd->redir_nb);
		while (i < cmd->argc)
		{	
			if (cmd->type[i] < T_LOWER || cmd->type[i] > T_GGREATER)
				i++;
			else if (j < cmd->redir_nb)
			{
				if (ft_handleredir(j, cmd, &i) > 0)
				{
					cmd->redir_nb = j + 1;
					return (1);
				}
				j++;
			}
		}
	}
	return (0);
}

void	ft_countredir(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->av[i])
	{
		if (cmd->type[i] >= T_LOWER && cmd->type[i] <= T_GGREATER)
			cmd->redir_nb++;
		i++;
	}
	printf("test %d : i, %d : argc\n", i, cmd->argc);
}

int	ft_handleredir(int j, t_cmd *cmd, int *i)
{
	cmd->redir[j].type = cmd->type[*i];
	if (cmd->redir[j].type == T_GREATER)
		return (ft_greaterstart(cmd, *i, j));
	else if (cmd->redir[j].type == T_GGREATER)
		return (ft_ggreaterstart(cmd, *i, j));
	else if (cmd->redir[j].type == T_LOWER)
		return (ft_lowerstart(cmd, *i, j));
	else if (cmd->redir[j].type == T_LLOWER)
		return (ft_llowerstart(cmd, *i, j));
	return (0);
}

void	ft_endredir(t_cmd *cmd)
{
	int	i;

	i = cmd->redir_nb - 1;
	while (i >= 0 && cmd->redir[i].fd && cmd->redir[i].fd != -1)
	{
		if (cmd->redir[i].type == T_GREATER || cmd->redir[i].type == T_GGREATER)
		{
			if (dup2(cmd->redir[i].fdsave, STDOUT_FILENO) == -1)
				printf("error reestablish stdout\n");
		}
		else if (cmd->redir[i].type == T_LOWER
			|| cmd->redir[i].type == T_LLOWER)
		{
			if (dup2(cmd->redir[i].fdsave, STDIN_FILENO) == -1)
				printf("error reestablish stdin\n");
		}
		if (close(cmd->redir[i].fdsave) == -1 || close(cmd->redir[i].fd) == -1)
			printf ("error close\n");
		i--;
	}
	free(cmd->redir);
}
