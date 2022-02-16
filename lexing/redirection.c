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

void	ft_lowerstart(t_cmd *cmd, int i, int j)
{
	if (cmd->type[i] == T_LOWER)
	{
		cmd->redir[j].fd = open(cmd->av[i + 1], O_RDONLY);
		if (cmd->redir[j].fd == -1)
		{
			printf("error open\n");
			return ;
		}
	}
	modif_arg(&cmd);
	ft_redirstd(&cmd->redir[j], STDIN_FILENO);
}

void	ft_llowerstart(t_cmd *cmd, int i, int j)
{
	char	*buffer;
	char	*delimiter;

	printf("delim %s \n", cmd->av[i + 1]);
	if (ft_isquote(cmd->av[i + 1][0]) > 0)
		delimiter = ft_handle_quote(cmd->av[i + 1], &j, 0);
	else
		delimiter = ft_strdup(cmd->av[i + 1]);
	printf("delim %s \n", delimiter);
	buffer = readline("heredoc> ");
	cmd->redir[j].fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0650);
	if (cmd->redir->fd == -1)
	{
		printf("error open\n");
		return ;
	}
	while (buffer && ft_strcmp(buffer, delimiter) != 0)
		// ft_write_heredoc(&buffer, cmd, j);
		{
	if (has_dollar(buffer) > 0)
		buffer = ft_extract_var(buffer);
	write(cmd->redir[j].fd, buffer, ft_strlen(buffer));
	write(cmd->redir[j].fd, "\n", 2);
	free(buffer);
	buffer = readline("heredoc>");
	printf("delim %s \n", delimiter);
}
	free(buffer);
	free(delimiter);
	modif_arg_heredoc(&cmd, ".heredoc");
	ft_redirstd(&cmd->redir[j], STDIN_FILENO);
}

void	ft_greaterstart(t_cmd *cmd, int i, int j)
{
	cmd->redir[j].fd = open(cmd->av[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0650);
	if (cmd->redir[j].fd == -1)
	{
		printf("error open\n");
		return ;
	}
	modif_arg(&cmd);
	ft_redirstd(&cmd->redir[j], STDOUT_FILENO);
}

void	ft_ggreaterstart(t_cmd *cmd, int i, int j)
{
	cmd->redir[j].fd = open(cmd->av[i + 1], O_RDWR | O_CREAT | O_APPEND, 0650);
	if (cmd->redir[j].fd == -1)
	{
		printf("error open\n");
		return ;
	}
	modif_arg(&cmd);
	ft_redirstd(&cmd->redir[j], STDOUT_FILENO);
}
