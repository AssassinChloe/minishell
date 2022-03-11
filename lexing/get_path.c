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

int	ft_lauch_cmd(char **cmd, char *path)
{
	if (path == NULL)
		return (127);
	else
	{
		free(*cmd);
		*cmd = ft_strdup(path);
		free(path);
		return (0);
	}
}

void	ft_concat_path(char *path_split, char **path, char **cmd)
{
	*path = ft_strdup(path_split);
	*path = ft_strjoin(*path, "/");
	*path = ft_strjoin(*path, *cmd);
	if (!*path)
		printf("error malloc\n");
}

void	ft_checkpath(char **path_split, char **path, char **cmd, int i)
{
	int	j;

	j = 0;
	while (j < i && access(*path, F_OK | X_OK) != 0)
	{
		free(*path);
		*path = NULL;
		j++;
		if (j < i)
			ft_concat_path(path_split[j], path, cmd);
	}
}

int	ft_get_cmd_path(char **cmd)
{
	char	*path;
	char	**path_split;
	int		i;
	char	*tmp;

	if (access(*cmd, F_OK | X_OK) != 0)
	{
		i = 0;
		path = NULL;
		tmp = get_env_value("PATH");
		if (tmp == NULL)
			return (0);
		path_split = ft_split(tmp, ":");
		free(tmp);
		tmp = NULL;
		while (path_split[i])
			i++;
		ft_concat_path(path_split[0], &path, cmd);
		ft_checkpath(path_split, &path, cmd, i);
		free_table_string(path_split);
		i = ft_lauch_cmd(cmd, path);
		if (i > 0)
			return (i);
	}
	return (0);
}
