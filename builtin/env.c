/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 10:30:34 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/01 10:31:45 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_last_env(void)
{
	t_env	*env;

	env = g_data.env;
	if (!env)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	modify_shlvl_value(void)
{
	char	*tmp;
	int		num;

	tmp = get_env_value("SHLVL");
	num = ft_atoi(tmp);
	num++;
	free(tmp);
	tmp = NULL;
	tmp = ft_itoa(num);
	change_env_value("SHLVL", ft_strdup(tmp), 1);
	free(tmp);
}

char	*env_in_string(t_env *var)
{
	char	*tmp;

	tmp = ft_strdup(var->key);
	tmp = ft_strjoin_char(tmp, '=');
	tmp = ft_strjoin_d(tmp, get_env_value(var->key));
	return (tmp);
}

char	**ft_env_in_tab(void)
{
	char	**tab_env;
	char	*tmp;
	int		i;
	t_env	*var;

	i = 0;
	var = g_data.env;
	free_table_string(g_data.env_in_tab);
	tab_env = (char **)malloc(sizeof(char *) * (count_var_env() + 2));
	while (i <= count_var_env())
	{
		if (var->has_value)
		{
			tmp = env_in_string(var);
			tab_env[i] = ft_strdup(tmp);
			free(tmp);
		}
		else
			tab_env[i] = ft_strdup(var->key);
		i++;
		var = var->next;
	}
	tab_env[i] = NULL;
	return (tab_env);
}

/*
//uniquement pour test
int	print_table_string(char **table)
{
	int		i;

	i = 0;
	while (table[i])
	{
		ft_putendl_fd(table[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
*/

int	ft_env(t_cmd cmd)
{
	t_env	*var;

	if (cmd.argc!= 1)
	{
		ft_putstr_fd("env : ", STDOUT_FILENO);
		ft_putstr_fd(cmd.av[1], STDOUT_FILENO);
		ft_putendl_fd(": Syntax error : read the subject !", STDOUT_FILENO);
		g_data.exit_value = 127;
		return (127);
	}
	var = g_data.env;
	while (var)
	{
		if (var->has_value)
		{
			ft_putstr_fd(var->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(var->value, STDOUT_FILENO);
		}
		var = var->next;
	}
	return (0);
}

/*
int	ft_env(t_cmd cmd)
{
	t_env	*var;

	(void)cmd;
	if (cmd.argc!= 1)
	{
		ft_putstr_fd("env : ", STDOUT_FILENO);
		ft_putstr_fd(cmd.av[1], STDOUT_FILENO);
		ft_putendl_fd(": No such file or directory", STDOUT_FILENO);
		g_data.exit_value = 127;
		return (0);
	}
	var = g_data.env;
	while (var)
	{
		if (var->has_value)
		{
			ft_putstr_fd(var->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(var->value, STDOUT_FILENO);
		}
		var = var->next;
	}
	return (0);
}
*/