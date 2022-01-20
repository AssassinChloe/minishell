/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 13:21:55 by vmercier          #+#    #+#             */
/*   Updated: 2021/05/25 13:23:43 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*prev;

	if (lst && *lst && del)
	{
		prev = (t_list *)*lst;
		while (prev)
		{
			temp = prev->next;
			ft_lstdelone(prev, del);
			prev = temp;
		}
		*lst = NULL;
	}
}
