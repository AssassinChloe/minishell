/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 22:03:56 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/13 22:13:54 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirstd(t_redir *redir, int std)
{
	redir->fdsave = dup(std);
	if (redir->fdsave == -1)
		printf("error copie fd\n");
	if (dup2(redir->fd, std) == -1)
		printf("error redirection\n");
}

int	ft_lowerstart(t_cmd *cmd, int i, int j)
{
	if (cmd->type[i] == T_LOWER)
	{
		cmd->redir[j].fd = open(cmd->av[i + 1], O_RDONLY);
		if (cmd->redir[j].fd == -1)
		{
			error_message(cmd->av[i + 1]);
			return (1);
		}
	}
	modif_arg(&cmd);
	ft_redirstd(&cmd->redir[j], STDIN_FILENO);
	return (0);
}

int	ft_llowerstart(t_cmd *cmd, int i, int j)
{
	if (open_heredoc(cmd, i, j) > 0)
		return (1);
	modif_arg_heredoc(&cmd, ".heredoc");
	ft_redirstd(&cmd->redir[j], STDIN_FILENO);
	return (0);
}

int	ft_greaterstart(t_cmd *cmd, int i, int j)
{
	cmd->redir[j].fd = open(cmd->av[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0655);
	if (cmd->redir[j].fd == -1)
	{
		error_message(cmd->av[i + 1]);
		return (1);
	}
	modif_arg(&cmd);
	ft_redirstd(&cmd->redir[j], STDOUT_FILENO);
	return (0);
}

int	ft_ggreaterstart(t_cmd *cmd, int i, int j)
{
	cmd->redir[j].fd = open(cmd->av[i + 1], O_RDWR | O_CREAT | O_APPEND, 0655);
	if (cmd->redir[j].fd == -1)
	{
		error_message(cmd->av[i + 1]);
		return (1);
	}
	modif_arg(&cmd);
	ft_redirstd(&cmd->redir[j], STDOUT_FILENO);
	return (0);
}
