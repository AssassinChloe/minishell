/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:51:02 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/13 20:41:41 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_command(char *str)
{
	int		fd;
	char	*line;
	int		ret;
	int		isvalid;

	line = NULL;
	isvalid = 0;
	fd = open("lexing/commandes.txt", O_RDONLY);
	if (fd < 0)
		printf("erreur open\n");
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		if (ft_strcmp(str, line) == 0)
			isvalid = 1;
		free(line);
		line = NULL;
		ret = get_next_line(fd, &line);
	}
	if (ret < 0)
		printf("erreur gnl \n");
	free(line);
	line = NULL;
	close(fd);
	return (isvalid);
}

int	ft_isbuiltin(char *str)
{
	if (ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "export") == 0 || ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "env") == 0 || ft_strcmp(str, "exit") == 0
		|| ft_strcmp(str, "echo") == 0)
		return (0);
	return (1);
}

int	get_token_type(char *str, int *multicmd)
{
	if (ft_strcmp(str, "|") == 0)
		return (T_PIPE);
	else if (is_flag_n(str) == 1)
		return (T_FLAG);
	else if (ft_strcmp(str, "<") == 0)
		return (T_LOWER);
	else if (ft_strcmp(str, "<<") == 0)
		return (T_LLOWER);
	else if (ft_strcmp(str, ">") == 0)
		return (T_GREATER);
	else if (ft_strcmp(str, ">>") == 0)
		return (T_GGREATER);
	else if (*multicmd == 0 && ft_isbuiltin(str) == 0)
	{
		*multicmd = 1;
		return (T_BUILTIN);
	}
	else if (*multicmd == 0 && ft_is_command(str) == 1)
	{
		*multicmd = 1;
		return (T_CMD);
	}
	else
		return (T_STRING);
}

void	ft_printtype(t_list *elem)
{
	t_list	*tmp;
	t_cmd	*type;
	int		i;

	i = 0;
	tmp = elem;
	while (tmp)
	{
		type = (t_cmd *)tmp->content;
		printf(" il y a %d argument dans la ligne de commande : \n", type->argc);
		while (i < type->argc)
		{
			printf("type %d : %s\n", type->type[i], type->av[i]);
			i++;
		}
		i = 0;
		tmp = tmp->next;
	}
}

int	ft_lexing(t_list **list)
{
	t_list	*commandlist;

	commandlist = NULL;
	ft_divide_pipe(*list, *list, &commandlist);
	execute_command(commandlist);
//	ft_free_commandlist(&commandlist);
	return (0);
}
