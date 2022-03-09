/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:29:52 by cassassi          #+#    #+#             */
/*   Updated: 2022/03/08 17:29:57 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_split_list(char *str)
{
	t_split	*tmp_var;

	tmp_var = malloc(sizeof(t_split));
	tmp_var->str = ft_strdup(str);
	tmp_var->token_nb = g_data.token;
	if (g_data.split == NULL)
		g_data.split = ft_lstnew(tmp_var);
	else
		ft_lstadd_back(&g_data.split, ft_lstnew(tmp_var));
}

void	ft_free_splitlist(t_list **splitlist)
{
	t_list	*tmp;
	t_split	*split;

	tmp = *splitlist;
	while (tmp)
	{
		split = (t_split *)tmp->content;
		if (split->str)
			free(split->str);
		tmp = tmp->next;
	}
	ft_lstclear(splitlist);
}
