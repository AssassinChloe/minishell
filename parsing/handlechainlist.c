/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlechainlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:11:39 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/13 17:13:14 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printchain(t_list *elem)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = elem;
	while (tmp)
	{
		printf("token %d : -%s-\n", i, (char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
}

void	ft_addone(t_list **tokens, char **tmp)
{
	if (*tmp != NULL)
	{
		if (*tokens == NULL)
			*tokens = ft_lstnew(ft_strdup(*tmp));
		else
			ft_lstadd_back(tokens, ft_lstnew(ft_strdup(*tmp)));
		free(*tmp);
		*tmp = NULL;
	}
}
