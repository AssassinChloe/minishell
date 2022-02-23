/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:32:56 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/23 17:32:59 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_var(t_env *var)
{
	if (var->key)
		free(var->key);
	if (var->value)
		free(var->value);
	free(var);
}

void	clear_list(t_env **list)
{
	t_env	*var;
	t_env	*tmp;

	if (!list || !(*list))
		return ;
	var = *list;
	while (var)
	{
		tmp = var;
		var = var->next;
		destroy_var(tmp);
	}
	*list = NULL;
}

t_env	*record_var(char *key, char *value)
{
	t_env	*var;

	var = (void *)malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	var->has_value = 1;
	if (!value)
		var->has_value = 0;
	var->next = NULL;
	if (!var->key || !var->value)
	{
		destroy_var(var);
		var = NULL;
	}
	return (var);
}

t_env	*get_env(char **envp)
{
	t_env	*var_env;
	t_env	*var;
	char	**tmp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	var_env = NULL;
	while (i--)
	{
		tmp = ft_split_env(envp[i]);
		var = record_var(tmp[0], tmp[1]);
		if (!var)
		{
			free_tab2(tmp);
			clear_list(&var_env);
			break ;
		}
		var->next = var_env;
		var_env = var;
		free_tab2(tmp);
	}
	return (var_env);
}
