/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:44:06 by vmercier          #+#    #+#             */
/*   Updated: 2022/03/08 14:44:13 by vmercier         ###   ########.fr       */
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
	ft_putstr_fd("minishell: cd: too many arguments\n", STDOUT_FILENO);
	g_data.exit_value = 1;
	return (1);
}

int	err_cd_home_unset(char *srcpath, char *destpath)
{
	ft_putstr_fd("cd: HOME not set\n", STDOUT_FILENO);
	free(destpath);
	destpath = NULL;
	free(srcpath);
	srcpath = NULL;
	g_data.exit_value = 1;
	return (1);
}

int	err_cd_oldpwd_unset(char *srcpath, char *destpath)
{
	ft_putstr_fd("cd: OLDPWD not set\n", STDOUT_FILENO);
	free(destpath);
	destpath = NULL;
	free(srcpath);
	srcpath = NULL;
	g_data.exit_value = 1;
	return (1);
}
