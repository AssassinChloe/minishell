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

void	ft_free_commandlist(t_list **commandlist)
{
	t_list	*tmp;
	t_cmd	*type;
	int		i;

	tmp = *commandlist;
	while (tmp)
	{
		type = (t_cmd *)tmp->content;
		i = 0;
		while (i < (type->argc_init))
		{
			if (type->av[i])
				free(type->av[i]);
			i++;
		}
		if (type->av)
			free(type->av);
		if (type->type)
			free(type->type);
		tmp = tmp->next;
	}
	ft_lstclear(commandlist);
}

int	ft_divide_redirection(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_countredir(cmd);
	if (cmd->redir_nb > 0)
	{
		cmd->redir = malloc(sizeof(t_redir) * cmd->redir_nb);
		while (i < cmd->argc)
		{	
			if (cmd->type[i] < T_LOWER || cmd->type[i] > T_GGREATER)
				i++;
			if (j < cmd->redir_nb && (cmd->type[i] >= T_LOWER
					&& cmd->type[i] <= T_GGREATER))
			{
				if (ft_handleredir(j, cmd, &i) > 0)
				{
					cmd->redir_nb = j + 1;
					return (1);
				}
				j++;
			}
		}
	}
	return (0);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_add_mem(t_cmd **cmd, int k)
{
	char	**tmp_av;
	int		*tmp_ac;
	int		i;

	i = 0;
	while ((*cmd)->av[i])
		i++;
	tmp_av = malloc(sizeof(char *) * (i + k + 1));
	tmp_ac = malloc(sizeof(int) * (i + k));
	i = 0;
	while ((*cmd)->av[i])
	{
		tmp_av[i] = ft_strdup((*cmd)->av[i]);
		free((*cmd)->av[i]);
		(*cmd)->av[i] = NULL;
		tmp_ac[i] = (*cmd)->type[i];
		i++;
	}
	tmp_av[i] = NULL;
	free((*cmd)->av);
	(*cmd)->av = tmp_av;
	free((*cmd)->type);
	(*cmd)->type = tmp_ac;
}

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
	j = 0;
	if (list != NULL)
		var = (t_split *)list->content;
	tmp->argc = i;
	tmp->argc_init = i;
	tmp->redir_nb = 0;
	k = 0;
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
			tmp->argc = tmp->argc + k - 1;
			tmp->argc_init = tmp->argc_init + k - 1;
			free_tab(split);
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
		tmp->av[j] = NULL;
		*token = *token + 1;
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
