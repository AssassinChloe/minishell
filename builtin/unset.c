/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:48:10 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/16 13:48:16 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
si arg = nom d'une variable -> suppression de cette variable
g_data.exit_value = 0

si arg = nom nom valide (ex : contient - ) : 
message error : not a valid identifier
g_data.exit_value = 1

si pas d'arg -> ne fait rien
g_data.exit_value = 0

si plusieurs arguments : 
traite tous les arguments les uns a la suite des autres, 
ne s'arrette pas si erreur
*/

void	del_first_env(t_env *tmp)
{
	tmp = g_data.env->next;
	if ((g_data.env)->key)
		free((g_data.env)->key);
	if ((g_data.env)->value)
		free((g_data.env)->value);
	if (g_data.env)
		free(g_data.env);
	g_data.env = NULL;
	g_data.env = tmp;
}

t_env	*get_prev(char *key)
{
	t_env	*tmp;

	tmp = g_data.env;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->next->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	unset_invalid(char *str)
{
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_data.exit_value = 1;
	return (1);
}

int	ft_unset(char **arg)
{
	t_env	*prev;
	t_env	*tmp;
	int		i;
	int 	ret;

	i = 0;
	ret = 0;
	while (arg[++i])
	{
		if (!format_key_ok(arg[i]))
			ret = unset_invalid(arg[i]);
		tmp = NULL;
		if (already_in_env(arg[i]))
		{
			prev = get_prev(arg[i]);
			if (prev)
			{
				tmp = prev->next->next;
				destroy_var_env(prev->next);
				prev->next = tmp;
			}
			else
				del_first_env(tmp);
		}
	}
	return (ret);
}

/*
int	ft_unset(char **arg)
{
	t_env	*prev;
	t_env	*tmp;
	int		i;

	i = 0;
	while (arg[++i])
	{
		if (!format_key_ok(arg[i]))
			return (unset_invalid(arg[i]));
		tmp = NULL;
		if (!already_in_env(arg[i]))
			return (0);
		prev = get_prev(arg[i]);
		tmp = prev->next->next;
		if (!tmp)
		{
			prev->next = NULL;
			return (0);
		}
		destroy_var_env(prev->next);
//		if (prev->next->value)
//			free(prev->next->value);
//		if (prev->next->key)
//			free(prev->next->key);
//		free(prev->next);
		prev->next = tmp;
	}
	destroy_var_env(tmp);
	return (0);
}
*/