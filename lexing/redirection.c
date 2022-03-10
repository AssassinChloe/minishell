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

void	error_message(char *cmd)
{
	char *error;
	char *tmp;

	tmp = ft_strdup(cmd);
	error = ft_strdup("minishell: ");
	error = ft_strjoin(error, tmp);
	free(tmp);
	tmp = NULL;
	error = ft_strjoin(error, ": No such file or directory\n");
	write(STDERR_FILENO, error, (ft_strlen(error) + 1));
	free(error);
	error = NULL;
}

int	open_heredoc(t_cmd *cmd, int i, int j)
{
	char	*buffer;
	char	*delimiter;
	int		isquote;

	isquote = 0;
	if (ft_isquote(cmd->av[i + 1][0]) > 0)
		delimiter = ft_handle_quote(cmd->av[i + 1], &isquote, 0);
	else
		delimiter = ft_strdup(cmd->av[i + 1]);
	buffer = readline("heredoc> ");
	cmd->redir[j].fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0755);
	if (cmd->redir->fd == -1)
	{
		write(STDERR_FILENO, "minishell: .heredoc: Permission denied\n", 41);
		free(buffer);
		free(delimiter);
		return (1);
	}
	while (buffer && ft_strcmp(buffer, delimiter) != 0)
		ft_write_heredoc(&buffer, cmd, j, isquote);
	free(buffer);
	free(delimiter);
	return (0);
}

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
