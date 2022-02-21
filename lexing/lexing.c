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
	else if (*multicmd == 0)
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

int	test_iscmd(t_list *cmdlist)
{
	struct stat	*test;
	t_cmd	*cmd;
	t_list	*command;
	int i;

	i = 0;
	command = cmdlist;
	cmd = NULL;
	test = NULL;
	while (command)
	{
		cmd = (t_cmd *)command->content;
		test = malloc(sizeof(struct stat));
		if (stat(cmd->av[0], test) >= 0 && S_ISDIR(test->st_mode) == 1)
		{
			printf("%s is a directory\n", cmd->av[0]);
			free(test);
			test = NULL;
			return (126);
		}
		free(test);
		test = NULL;
		if (ft_get_cmd_path(cmd) > 0)
				return (127);
		command = command->next;
		printf("%d\n", i++);
	}
	return (0);
}

int	ft_lexing(t_list **list)
{
	t_list	*commandlist;

	commandlist = NULL;
	ft_divide_pipe(*list, *list, &commandlist);
	g_data.exit_value = test_iscmd(commandlist);
	if (g_data.exit_value > 0)
	{
		ft_free_commandlist(&commandlist);
		return (1);
	}
	execute_command(commandlist);
	ft_free_commandlist(&commandlist);
	return (0);
}
