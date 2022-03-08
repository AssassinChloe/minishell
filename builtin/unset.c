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

void	del_first_env(void)
{
	t_env	*tmp;

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

int	unset_invalid_id(char *str)
{
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_data.exit_value = 1;
	return (1);
}

int	unset_invalid_option(char *str)
{
	ft_putstr_fd("unset: ", 2);
	ft_putchar_fd(str[0], 2);
	ft_putchar_fd(str[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
	g_data.exit_value = 2;
	return (2);
}

void	unset_has_prev(t_env *prev)
{
	t_env	*tmp;

	tmp = prev->next->next;
	destroy_var_env(prev->next);
	prev->next = tmp;
}

int	ft_unset(char **arg)
{
	t_env	*prev;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (arg[++i])
	{
		if (arg[1][0] == '-' && arg[1][1])
			return (unset_invalid_option(arg[1]));
		if (!format_key_ok(arg[i]))
			ret = unset_invalid_id(arg[i]);
		if (already_in_env(arg[i]))
		{
			prev = get_prev(arg[i]);
			if (prev)
				unset_has_prev(prev);
			else
				del_first_env();
		}
	}
	return (ret);
}
