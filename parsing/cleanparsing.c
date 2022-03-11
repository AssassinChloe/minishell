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

void	ft_freeparsing(t_parse **parse)
{
	t_list	*list;

	list = (*parse)->tokens;
	if ((*parse)->tmp)
		free((*parse)->tmp);
	(*parse)->tmp = NULL;
	ft_lstclear(&list);
	free(*parse);
}

char	*is_forbidden_redir(t_parse *parse)
{
	parse->i = -1;
	printf("minishell: syntax error\n");
	parse->multiple = 0;
	g_data.exit_value = 2;
	return (NULL);
}

char	*ft_remove_dollar(char *str, int start)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if ((ft_strlen(str) - 1) > 0)
	{
		tmp = malloc(ft_strlen(str));
		while (i < (start))
		{
			tmp[i] = str[i];
			i++;
		}
		while (str[i] != '$')
		{
			tmp[i] = str[i];
			i++;
		}
		tmp[i] = '\0';
	}
	free(str);
	str = NULL;
	return (tmp);
}
