/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:57:14 by cassassi          #+#    #+#             */
/*   Updated: 2022/03/10 16:57:19 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_redir_error(t_cmd *command)
{
	ft_endredir(command);
	g_data.exit_value = 1;
	close(g_data.check);
	return (1);
}

void	error_message(char *cmd)
{
	char	*error;
	char	*tmp;

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
