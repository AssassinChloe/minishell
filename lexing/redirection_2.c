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

void	ft_countredir(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->argc)
	{
		if (cmd->type[i] >= T_LOWER && cmd->type[i] <= T_GGREATER)
			cmd->redir_nb++;
		i++;
	}
}

void	ft_handleredir(int j, t_cmd *cmd, int *i)
{
	cmd->redir[j].type = cmd->type[*i];
	if (cmd->redir[j].type == T_GREATER)
		ft_greaterstart(cmd, *i, j);
	else if (cmd->redir[j].type == T_GGREATER)
		ft_ggreaterstart(cmd, *i, j);
	else if (cmd->redir[j].type == T_LOWER)
		ft_lowerstart(cmd, *i, j);
	else if (cmd->redir[j].type == T_LLOWER)
		ft_llowerstart(cmd, *i, j);
}

void	ft_endredir(t_cmd *cmd)
{
	int	i;

	i = cmd->redir_nb - 1;
	while (i >= 0)
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

void	ft_write_heredoc(char **buffer, t_cmd *cmd, int j, int isquote)
{
	if (isquote == 0 && has_dollar(*buffer) > 0)
		*buffer = ft_extract_var(*buffer);
	write(cmd->redir[j].fd, *buffer, ft_strlen(*buffer));
	write(cmd->redir[j].fd, "\n", 1);
	free(*buffer);
	*buffer = readline("heredoc>");
}
