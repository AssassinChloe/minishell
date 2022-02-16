/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:27:06 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/14 10:32:05 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **path_split)
{
	int	i;

	i = 0;
	while (path_split[i])
	{
		free(path_split[i]);
		i++;
	}
	free(path_split);
}

void	ft_lauch_cmd(t_cmd *cmd, char *path)
{
	if (path == NULL)
	{
		printf("command not found\n");
		return ;
	}
	else
	{
		free(cmd->av[0]);
		cmd->av[0] = ft_strdup(path);
		free(path);
	}
	exec_cmd(cmd->av);
}

void	ft_concat_path(char *path_split, char **path, char *cmd)
{
	*path = ft_strdup(path_split);
	*path = ft_strjoin(*path, "/");
	*path = ft_strjoin(*path, cmd);
	if (!*path)
		printf("error malloc\n");
}

void	ft_get_cmd_path(t_cmd *cmd)
{
	char	*path;
	char	**path_split;
	int		i;
	int		j;

	printf("builtin in get_path ? %d", ft_isbuiltin(cmd->av[0])); //
	if (ft_isbuiltin(cmd->av[0])) //
		launch_builtin(cmd); //
	else
	{
		if (access(cmd->av[0], F_OK | X_OK) != 0)
		{
			i = 0;
			j = 0;
			path = NULL;
			path_split = ft_split(getenv("PATH"), ":");
			while (path_split[i])
				i++;
			ft_concat_path(path_split[j], &path, cmd->av[0]);
			while (j < i && access(path, F_OK | X_OK) != 0)
			{
				free(path);
				path = NULL;
				j++;
				if (j < i)
					ft_concat_path(path_split[j], &path, cmd->av[0]);
			}
			ft_free_tab(path_split);
			ft_lauch_cmd(cmd, path);
		}
	}
}
