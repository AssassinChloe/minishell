/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_around_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:17:40 by cassassi          #+#    #+#             */
/*   Updated: 2022/03/12 12:17:44 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tmp(t_cmd *tmp)
{
	int	j;

	j = 0;
	while (tmp->av[j])
	{
		free(tmp->av[j]);
		tmp->av[j] = NULL;
		j++;
	}
	free(tmp->av);
	tmp->av = NULL;
	free(tmp->type);
	tmp->type = NULL;
	free(tmp);
	tmp = NULL;
}

int	ft_find_pipe(t_list **tmplist)
{
	int	i;

	i = 0;
	while (*tmplist && ft_strcmp((char *)(*tmplist)->content, "|") != 0)
	{
		i++;
		*tmplist = (*tmplist)->next;
	}
	if (*tmplist && ft_strcmp((char *)(*tmplist)->content, "|") == 0)
	{
		(*tmplist) = (*tmplist)->next;
		g_data.nb_pipe++;
	}
	return (i);
}

int	ft_divide_pipe(t_list *tmplist, t_list *tmplist2, t_list **commandlist)
{
	int		i;
	t_cmd	*tmp;
	int		token;

	token = 0;
	while (tmplist)
	{
		tmp = malloc(sizeof(t_cmd));
		i = ft_find_pipe(&tmplist);
		tmplist2 = ft_build_cmdlist(tmp, i, tmplist2, &token);
		if (*commandlist == NULL)
			*commandlist = ft_lstnew(tmp);
		else
			ft_lstadd_back(commandlist, ft_lstnew(tmp));
	}
	return (0);
}
