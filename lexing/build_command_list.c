/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:57:02 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/13 22:45:54 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_split_token(char *token, int *j, int *cmd, t_cmd **tmp)
{
	int		k;
	char	**split;

	k = 0;
	split = ft_split(token, " ");
	while (split[k])
		k++;
	ft_set_mem(tmp, k);
	k = 0;
	while (split[k])
	{
		(*tmp)->av[*j] = ft_strdup(split[k]);
		if (j == 0)
			(*tmp)->type[*j] = get_type(token, cmd);
		else
			(*tmp)->type[*j] = T_FILENAME;
		k++;
		*j = *j + 1;
	}
	if (k > 1)
	{
		(*tmp)->argc = (*tmp)->argc + k - 1;
		(*tmp)->argc_init = (*tmp)->argc;
	}
	free_table_string(split);
}

t_list	*end_pipe(t_list *tmplist2, int *token)
{
	if (tmplist2 && ft_strcmp((char *)tmplist2->content, "|") == 0)
	{
		tmplist2 = tmplist2->next;
		*token = *token + 1;
	}
	return (tmplist2);
}

void	ft_init_cmdlist(int i, int *j, int *cmd, t_cmd **tmp)
{
	*cmd = 0;
	*j = 0;
	(*tmp)->argc = i;
	(*tmp)->argc_init = i;
	(*tmp)->redir_nb = 0;
	(*tmp)->av = NULL;
	(*tmp)->type = NULL;
}

void	add_token(t_list *tmplist2, t_cmd **tmp, int *j, int *cmd)
{
	ft_set_mem(tmp, 1);
	(*tmp)->av[*j] = ft_strdup((char *)tmplist2->content);
	if (*j > 0 && ((*tmp)->type[*j - 1] >= T_LOWER
			&& (*tmp)->type[*j - 1] <= T_GGREATER))
		(*tmp)->type[*j] = T_FILENAME;
	else
		(*tmp)->type[*j] = get_type((char *)tmplist2->content, cmd);
	*j = *j + 1;
}

t_list	*ft_build_cmdlist(t_cmd *tmp, int i, t_list *tmplist2, int *token)
{
	int		j;
	int		cmd;
	t_split	*var;
	t_list	*list;

	ft_init_cmdlist(i, &j, &cmd, &tmp);
	list = g_data.split;
	if (list != NULL)
		var = (t_split *)list->content;
	while (tmplist2 && tmp->argc > j)
	{
		if (list && *token == var->token_nb)
		{
			ft_split_token((char *)tmplist2->content, &j, &cmd, &tmp);
			list = list->next;
			if (list != NULL)
				var = (t_split *)list->content;
		}
		else
			add_token(tmplist2, &tmp, &j, &cmd);
		tmp->av[j] = NULL;
		*token = *token + 1;
		tmplist2 = tmplist2->next;
	}
	return (end_pipe(tmplist2, token));
}
