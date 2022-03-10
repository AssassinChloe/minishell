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
