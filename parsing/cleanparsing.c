/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanparsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:09:51 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/13 18:11:45 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freeparsing(char **str, t_list **chain)
{
	free(*str);
	*str = NULL;
	ft_lstclear(chain);
}

int	is_forbidden_char(char c)
{
	if (c == ';' || c == 92 || c == '!' || c == ':')
		return (1);
	return (0);
}

char	*is_forbidden_redir(int *i, int *multiple)
{
	*i = -1;
	printf("error specific char without arg between or after\n");
	*multiple = 0;
	return (NULL);
}
