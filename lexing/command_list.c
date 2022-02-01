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
		while (i < type->argc)
		{
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

void ft_divide_redirection(t_list *commandlist)
{
	t_cmd *tmp;
	int i;
	int fd;
	int ret;
	int fdsave;
	char *buffer;
	char	*heredoc;

	while (commandlist)
	{
		i = 0;
		tmp = (t_cmd *)commandlist->content;
		while (i < tmp->argc && (tmp->type[i] < T_LOWER || tmp->type[i] > T_GGREATER))
			i++;
		if (i < tmp->argc && (tmp->type[i] == T_GREATER || tmp->type[i] == T_GGREATER))
		{
			free(tmp->argv[i]);
			tmp->argv[i] = NULL;
			if (tmp->type[i] == T_GREATER)
			{
				fd = open(tmp->argv[i + 1], O_RDWR|O_CREAT|O_TRUNC, 0777);
				if (fd == -1)
				{
					printf("error open\n");
					return ;
				}
			}
			else if (tmp->type[i] == T_GGREATER)
			{
				fd = open(tmp->argv[i + 1], O_RDWR|O_CREAT|O_APPEND, 0777);
				if (fd == -1)
				{
					printf("error open\n");
					return ;
				}
			}
			fdsave = dup(STDOUT_FILENO);
			if (fdsave == -1)
				printf("error copie stout\n");
			ret = dup2(fd, STDOUT_FILENO);
			if (ret == -1)
				printf("error redirection\n");
		}
		else if (i < tmp->argc && (tmp->type[i] == T_LOWER || tmp->type[i] == T_LLOWER))
		{
			free(tmp->argv[i]);
			if (tmp->type[i] == T_LOWER)
			{
				tmp->argv[i] = NULL;
				fd = open(tmp->argv[i + 1], O_RDONLY);
				if (fd == -1)
				{
					printf("error open\n");
					return ;
				}
				fdsave = dup(STDIN_FILENO);
				if (fdsave == -1)
					printf("error copie stdin\n");
				ret = dup2(fd, STDIN_FILENO);
				if (ret == -1)
					printf("error redirection\n");
			}
			else if (tmp->type[i] == T_LLOWER)
			{
				heredoc = NULL;
				buffer = readline("heredoc> ");
				while (buffer && ft_strcmp(buffer, tmp->argv[i + 1]) != 0)
				{
					heredoc = ft_strjoin(heredoc, buffer);
					heredoc = ft_strjoin_char(heredoc, '\n');
					buffer = readline("heredoc>");
				}
				tmp->argv[i] = ft_strdup(heredoc);
				free(heredoc);
				free(tmp->argv[i + 1]);
				tmp->argv[i + 1] = NULL;				
			}
		}
		ft_execution_test(tmp);
		if (i < tmp->argc && (tmp->type[i] == T_GREATER || tmp->type[i] <= T_GGREATER))
		{
			ret = dup2(fdsave, STDOUT_FILENO);
			if (ret == -1)
				printf("error reestablish stdout\n");
			if (close(fdsave) == -1 || close(fd) == -1)
				printf ("error close\n");
		}
		else if (i < tmp->argc && tmp->type[i] == T_LOWER)
		{	
			ret = dup2(fdsave, STDIN_FILENO);
			if (ret == -1)
				printf("error reestablish stdin\n");
			if (close(fdsave) == -1 || close(fd) == -1)
				printf ("error close\n");
		}
		commandlist = commandlist->next;
		/*if (commandlist)
		 * ==> il faut ouvrir un pipe voir même avant l'execution?*/
		
	}
}
