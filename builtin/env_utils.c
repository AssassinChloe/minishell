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

void	add_env_value(char *newkey, char *newvalue, int int_value)
{
	t_env	*last;
	t_env	*new;

	last = g_data.env;
	new = malloc(sizeof(char *) * 3);
	new->key = ft_strdup(newkey);
	new->value = ft_strdup(newvalue);
	new->has_value = int_value;
	new->next = NULL;
//	printf("New value : key = %s, value = %s, has_value = %d\n", 
//		new->key, new->value, new->has_value); //
	last = find_last_env();
	last->next = new;
//	printf("Last value : key = %s, value = %s, next key = %s\n", 
//		last->key, last->value, last->next->key); //
}