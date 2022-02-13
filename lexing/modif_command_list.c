/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_command_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 22:31:37 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/13 22:32:02 by cassassi         ###   ########.fr       */
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
	(*cmd)->argc = (*cmd)->argc - 2;
}

void	modif_arg(t_cmd **cmd)
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
	(*cmd)->av[j] = NULL;
	free((*cmd)->av[j + 1]);
	(*cmd)->av[j + 1] = NULL;
	j = j + 2;
	copy_and_free_end(cmd, j, i);
	return ;
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
	return ;
}
