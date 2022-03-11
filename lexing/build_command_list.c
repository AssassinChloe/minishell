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

t_list	*ft_init_cmdlist(t_cmd *tmp, int i, t_list *tmplist2, int *token)
{
	int		j;
	int		multicmd;
	char	**split;
	int		k;
	t_split	*var;
	t_list	*list;

	multicmd = 0;
	list = g_data.split;
	if (list != NULL)
		var = (t_split *)list->content;
	j = 0;
	tmp->argc = i;
	tmp->argc_init = i;
	tmp->redir_nb = 0;
	tmp->av = malloc(sizeof(char *) * (i + 1));
	tmp->type = malloc(sizeof(int) * i);
	while (tmplist2 && i > j)
	{
		if (list && *token == var->token_nb)
		{
			k = 0;
			split = ft_split((char *)tmplist2->content, " ");
			while (split[k])
				k++;
			if (k > 1)
				ft_add_mem(&tmp, k);
			k = 0;
			while (split[k])
			{
				tmp->av[j] = ft_strdup(split[k]);
				if (j == 0)
					tmp->type[j] = get_token_type((char *)tmplist2->content, &multicmd);
				else
					tmp->type[j] = T_FILENAME;
				k++;
				j++;
			}
			if (k >= 1)
			{
				tmp->argc = tmp->argc + k - 1;
				tmp->argc_init = tmp->argc_init + k - 1;
			}
			free_table_string(split);
			list = list->next;
			if (list != NULL)
				var = (t_split *)list->content;
		}
		else
		{
			tmp->av[j] = ft_strdup((char *)tmplist2->content);
			if (j > 0 && (tmp->type[j - 1] >= T_LOWER && tmp->type[j - 1] <= T_GGREATER))
				tmp->type[j] = T_FILENAME;
			else
				tmp->type[j] = get_token_type((char *)tmplist2->content, &multicmd);
			j++;
		}
		*token = *token + 1;
		tmp->av[j] = NULL;
		tmplist2 = tmplist2->next;
	}
	if (multicmd == 0)
	{
		tmp->argc = -1;
		if (tmp->type[0] == T_LLOWER)
		{	
			tmp->redir = malloc(sizeof(t_redir));
			open_heredoc(tmp, 0, 0);
			close(tmp->redir[0].fd);
			free(tmp->redir);
		}
		return (tmplist2);
	}
	if (tmplist2 && ft_strcmp((char *)tmplist2->content, "|") == 0)
		tmplist2 = tmplist2->next;
	return (tmplist2);
}

int	ft_divide_pipe(t_list *tmplist, t_list *tmplist2, t_list **commandlist)
{
	int		i;
	t_cmd	*tmp;
	int		token;

	token = 0;
	while (tmplist)
	{
		i = 0;
		tmp = malloc(sizeof(t_cmd));
		while (tmplist && ft_strcmp((char *)tmplist->content, "|") != 0)
		{
			i++;
			tmplist = tmplist->next;
		}
		if (tmplist && ft_strcmp((char *)tmplist->content, "|") == 0)
		{
			tmplist = tmplist->next;
			g_data.nb_pipe++;
			token++;
		}
		tmplist2 = ft_init_cmdlist(tmp, i, tmplist2, &token);
		if (*commandlist == NULL)
			*commandlist = ft_lstnew(tmp);
		else
			ft_lstadd_back(commandlist, ft_lstnew(tmp));
		if (tmp->argc < 0)
			return (-1);
	}
	return (0);
}
