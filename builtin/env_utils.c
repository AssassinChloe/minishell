/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:17:48 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/21 14:17:56 by vmercier         ###   ########.fr       */
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

int	already_in_env(char *arg)
{
	t_env	*tmp;

	tmp = g_data.env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, arg))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	format_key_ok(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && !(str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	change_env_value(char *key, char *newvalue, int int_value)
{
	t_env	*tmp;
	char	*to_free;

	tmp = g_data.env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			break ;
		tmp = tmp->next;
	}
	if (!tmp->value)
		tmp->has_value = 0;
	to_free = tmp->value;
	tmp->value = ft_strdup(newvalue);
	free(newvalue);
	tmp->has_value = int_value;
	free (to_free);
	if (!tmp->value)
		return ;
}

void	add_env_value(char *newkey, char *newvalue, int int_value)
{
	t_env	*last;
	t_env	*new;

	last = g_data.env;
	new = malloc(sizeof(char *) * 4);
	new->key = ft_strdup(newkey);
	new->value = ft_strdup(newvalue);
	new->has_value = int_value;
	new->next = NULL;
	last = find_last_env();
	last->next = new;
}
