/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:46:36 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/16 13:46:46 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*search_var(char *str)
{
	t_env	*var;

	var = g_data.env;
	while (var)
	{
		if (!ft_strcmp(var->key, str))
			return (var);
		var = var->next;
	}
	return (NULL);
}

char	*get_env_value(char *str)
{
	char	*env_value;
	t_env	*tmp;

	tmp = search_var(str);
	if (!tmp)
		return (NULL);
	env_value = ft_strdup(tmp->value);
	return (env_value);
}

int	cd_too_many(void)
{
	ft_putstr_fd("minishell: cd: too many arguments", STDOUT_FILENO);
	g_data.exit_value = 1;
	return (1);
}

int	ft_cd(t_cmd cmd)
{
	char	*src_path;
	char	*dest_path;

	if (cmd.argc > 2)
		return (cd_too_many());
	src_path = getcwd(NULL, 0);
	if (cmd.argc == 1)
	{
		dest_path = get_env_value("HOME");
		if (!dest_path)
		{
			ft_putstr_fd("cd: HOME not set\n", STDOUT_FILENO);
			free(dest_path);
			free(src_path);
			g_data.exit_value = 1;
			return (1);
		}
	}
	else if (!ft_strcmp(cmd.av[1], "-"))
		dest_path = get_env_value("OLDPWD");
	else
		dest_path = ft_strdup(cmd.av[1]);
	if (chdir(dest_path))
	{
		ft_putstr_fd("minishell: cd: ", STDOUT_FILENO);
		ft_putstr_fd(cmd.av[1], STDOUT_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
//        free(dest_path);
//		free(src_path);
		g_data.exit_value = 1;
		return (1);
	}
	free(dest_path);
	dest_path = NULL;
	dest_path = getcwd(NULL, 0);
	free(search_var("OLDPWD")->value); 
	search_var("OLDPWD")->value = ft_strdup(src_path);
	free(search_var("PWD")->value); 
	search_var("PWD")->value = ft_strdup(dest_path);
	free(src_path);
	src_path = NULL;
	free(dest_path);
	dest_path = NULL;
	return (0);
}
