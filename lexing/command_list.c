/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:57:02 by cassassi          #+#    #+#             */
/*   Updated: 2022/01/31 17:16:43 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_free_commandlist(t_list **commandlist)
{
	t_list *tmp;
	t_cmd   *type;
	int     i;

	tmp = *commandlist;
	while(tmp)
	{
		type = (t_cmd *)tmp->content;
		i = 0;
		while (i < (type->argc))
		{
			if (type->argv[i])
				free(type->argv[i]);
			i++;
		}
		free(type->argv);
		free(type->type);
		tmp = tmp->next;
	}
	ft_lstclear(commandlist);
}

void    ft_divide_pipe(t_list *tmplist, t_list *tmplist2, t_list **commandlist)
{
	int     i;
	int     j;
	int     multicmd;
	t_cmd	*tmp;

	while (tmplist)
	{
		multicmd = 0;
		i = 0;
		j = 0;
		tmp = malloc(sizeof(t_cmd));
		while (tmplist && ft_strcmp((char*)tmplist->content, "|") != 0)
		{
			i++;
			tmplist = tmplist->next;
		}
		if (tmplist && ft_strcmp((char*)tmplist->content, "|") == 0)
			tmplist = tmplist->next;
		tmp->argc = i;
		tmp->argv = malloc(sizeof(char *) * (i + 1));
		tmp->type = malloc(sizeof(int) * i);
		while (tmplist2 && i > j)
		{

			tmp->argv[j] = ft_strdup((char *)tmplist2->content);
			tmp->type[j] = get_token_type((char*)tmplist2->content, &multicmd);
			if (j == 0 && (tmp->type[j] != T_CMD && tmp->type[j] != T_BUILTIN))
				printf("%s : command not in THE LIST\n", tmp->argv[j]);
			if (j > 0 && (tmp->type[j - 1] >= T_LOWER && tmp->type[j - 1] <= T_GGREATER))
				tmp->type[j] = T_FILENAME;
			tmplist2 = tmplist2->next;
			j++;
		}
		tmp->argv[j] = NULL;
		multicmd = 0;
		if (tmplist2 && ft_strcmp((char*)tmplist2->content, "|") == 0)
			tmplist2 = tmplist2->next;
		if (*commandlist == NULL)
			*commandlist = ft_lstnew(tmp);
		else
			ft_lstadd_back(commandlist, ft_lstnew(tmp));
	}
}

void	ft_endredir(t_cmd *cmd)
{
	int i;

	i = 0;
	while (i < cmd->redir_nb)
	{
		if (cmd->redir[i].type == T_GREATER || cmd->redir[i].type == T_GGREATER)
		{
			if (dup2(cmd->redir[i].fdsave, STDOUT_FILENO) == -1)
				printf("error reestablish stdout\n");
		}
		else if (cmd->redir[i].type == T_LOWER || cmd->redir[i].type == T_LLOWER)
		{
			if (dup2(cmd->redir[i].fdsave, STDIN_FILENO) == -1)
				printf("error reestablish stdin\n");
			if (cmd->redir[i].type == T_LLOWER)
			{
				if (unlink(".heredoc") == -1)
					printf("erreur unlink\n");
			}
		}
		if (close(cmd->redir[i].fdsave) == -1 || close(cmd->redir[i].fd) == -1)
			printf ("error close\n");
		i++;
	}
}

void ft_divide_redirection(t_list *commandlist)
{
	t_cmd *cmd;
	int i;
	int j;
	
	while (commandlist)
	{
		i = 0;
		j = 0;
		cmd = (t_cmd *)commandlist->content;
		cmd->redir_nb = ft_countredir(cmd);
		printf("nb_redir %d \n", cmd->redir_nb);
		cmd->redir = malloc(sizeof(t_redir) * cmd->redir_nb);
		while (i < cmd->argc)
		{	
			while ((cmd->type[i] < T_LOWER || cmd->type[i] > T_GGREATER))
				i++;
			if (j < cmd->redir_nb && (cmd->type[i] >= T_LOWER && cmd->type[i] <= T_GGREATER))
			{
				cmd->redir[j].type = cmd->type[i];
				if (cmd->redir[j].type == T_GREATER)
					ft_greaterstart(cmd, i, j);
				else if (cmd->redir[j].type == T_GGREATER)
					ft_ggreaterstart(cmd, i, j);
				else if (cmd->redir[j].type == T_LOWER)
					ft_lowerstart(cmd, i, j);
				else if (cmd->redir[j].type == T_LLOWER)
					ft_llowerstart(cmd, i, j);
				j++;
				printf("redir no %d \n", j);
			}
		}
		ft_execution_test(cmd);
		if (cmd->redir_nb > 0)
			ft_endredir(cmd);
		commandlist = commandlist->next;
		/*if (commandlist)
		 * ==> il faut ouvrir un pipe voir même avant l'execution?*/
	}
}
