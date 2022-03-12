/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:57:32 by cassassi          #+#    #+#             */
/*   Updated: 2022/03/10 16:57:39 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin_nopipe(t_cmd *command)
{
	if (ft_divide_redirection(command) > 0)
	{
		end_redir_error(command);
		return ;
	}
	launch_builtin(command);
	if (command->redir_nb > 0)
		ft_endredir(command);
}

void	ft_close_child(t_parse *parse)
{
	if (parse->i == 0)
	{
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		close(STDERR_FILENO);
		ft_freeparsing(&parse);
		ft_free_splitlist(&g_data.split);
		g_data.split = NULL;
		free_g_data();
		exit(EXIT_SUCCESS);
	}
}
