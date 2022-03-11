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
		while (i < type->argc)
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

void	copy_without_redir(t_cmd **cmd, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*cmd)->av[j] && ((*cmd)->type[j] < T_LOWER
			|| (*cmd)->type[j] > T_GGREATER))
	{
		tmp[i] = ft_strdup((*cmd)->av[j]);
		(*cmd)->type[i] = (*cmd)->type[j];
		j++;
		i++;
	}
	j+=2;
	while ((*cmd)->av[j])
	{
		tmp[i] = ft_strdup((*cmd)->av[j]);
		(*cmd)->type[i] = (*cmd)->type[j];
		j++;
		i++;
	}
	tmp[i] = NULL;
}

void	modif_arg(t_cmd **cmd)
{
	int	j;
	char **tmp;

	j = 0;
	while((*cmd)->av[j])
		j++;
	tmp = malloc(sizeof(char *) * (j + 1));
	copy_without_redir(cmd, tmp);
	j = 0;
	while ((*cmd)->av[j]) 
	{
		free((*cmd)->av[j]);
		(*cmd)->av[j] = NULL;
		j++;
	}
	free((*cmd)->av);
	(*cmd)->av = tmp;
	(*cmd)->argc = (*cmd)->argc - 2;
}
