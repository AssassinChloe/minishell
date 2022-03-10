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
		return (end_redir_error(command));
	launch_builtin(command);
	if (command->redir_nb > 0)
		ft_endredir(command);
}
