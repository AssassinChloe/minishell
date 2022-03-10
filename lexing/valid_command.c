/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:50:32 by cassassi          #+#    #+#             */
/*   Updated: 2022/03/02 23:50:36 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_for_env(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**trunc_list;
	int		*trunc_type;
	int		multicmd;

	i = 0;
	j = 0;
	multicmd = 0;
	while (cmd->av[i] && ft_strcmp(cmd->av[i], "env") == 0)
			i++;
	if (i > 0 && i < cmd->argc)
	{
		cmd->env = 1;
		trunc_list = malloc(sizeof(char *) * (cmd->argc - i + 1));
		trunc_type = malloc(sizeof(int) * (cmd->argc - i));
		while (i < cmd->argc)
		{
			trunc_type[j] = get_token_type(cmd->av[i], &multicmd);
			trunc_list[j++] = ft_strdup(cmd->av[i++]);
		}
		trunc_list[j] = NULL;
		while (i >= 0)
		{
			free(cmd->av[i]);
			cmd->av[i] = NULL;
			i--;
		}
		free(cmd->av);
		cmd->av = trunc_list;
		free(cmd->type);
		cmd->type = trunc_type;
		cmd->argc = j;
		cmd->argc_init = j;
	}
	else
		cmd->env = 0;
}

int	is_valid_cmd(t_cmd *cmd)
{
	struct stat	*test;
	int			ret;

	ret = 0;
	ft_check_for_env(cmd);
	test = malloc(sizeof(struct stat));
	if (cmd->av[0] && stat(cmd->av[0], test) >= 0 && S_ISDIR(test->st_mode) == 1)
	{	
		free(test);
		test = NULL;
		return (126);
	}
	free(test);
	test = NULL;
	if (ft_strcmp(cmd->av[0], "") == 0 || (cmd->type[0] != T_BUILTIN && ft_get_cmd_path(cmd) > 0))
		return (127);
	return (0);
}
