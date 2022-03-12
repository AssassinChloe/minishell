/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:08:16 by cassassi          #+#    #+#             */
/*   Updated: 2022/03/11 10:08:19 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_and_free_end(t_cmd **cmd, int j, int i)
{
	while ((*cmd)->av[j])
	{
		(*cmd)->av[i] = ft_strdup((*cmd)->av[j]);
		(*cmd)->type[i] = (*cmd)->type[j];
		j++;
		i++;
	}
	while ((*cmd)->av[i])
	{
		free((*cmd)->av[i]);
		(*cmd)->av[i] = NULL;
		(*cmd)->type[i] = 0;
		i++;
	}
}

void	modif_arg_heredoc(t_cmd **cmd, char *filename)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while ((*cmd)->av[j] && ((*cmd)->type[j] < T_LOWER
			|| (*cmd)->type[j] > T_GGREATER))
	{
		j++;
		i++;
	}
	free((*cmd)->av[j]);
	(*cmd)->av[i] = ft_strdup(filename);
	(*cmd)->type[i] = T_FILENAME;
	i++;
	free((*cmd)->av[j + 1]);
	(*cmd)->av[j + 1] = NULL;
	(*cmd)->type[i] = 0;
	j = j + 2;
	copy_and_free_end(cmd, j, i);
	(*cmd)->argc = (*cmd)->argc - 1;
	return ;
}

void	ft_write_heredoc(char **buffer, t_cmd *cmd, int j, int isquote)
{
	if (isquote == 0 && has_dollar(*buffer) > 0)
		*buffer = ft_extract(*buffer, 1, 0);
	write(cmd->redir[j].fd, *buffer, ft_strlen(*buffer));
	write(cmd->redir[j].fd, "\n", 1);
	free(*buffer);
	*buffer = readline("heredoc>");
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
