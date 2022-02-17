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

si arg = nom nom valide (ex : contient - ) : message error : not a valid identifier
g_data.exit_value = 1

si pas d'arg -> ne fait rien
g_data.exit_value = 0

si plusieurs arguments : 
traite tous les arguments les uns a la suite des autres, s'arrte si erreur
*/

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

int	ft_unset(char **arg)
{
	t_env	*prev;
	t_env	*tmp;
	int i;

	i = 1;
	while(arg[i])
	{
		tmp = NULL;
		printf("already_in_env ? %d\n", already_in_env(arg[i]));
		if (!already_in_env(arg[i]))
			return (0);
		prev = get_prev(arg[i]);
		printf("prev : key = %s, value = %s, next = %s\n",prev->key, prev->value, prev->next->key);
		tmp = prev->next->next;
		if (prev->next->value)
			free(prev->next->value);
		if (prev->next->key)
			free(prev->next->key);
		printf("prev apres : key = %s, value = %s, next = %s\n",prev->key, prev->value, prev->next->key);
		free(prev->next);
		prev->next = tmp;
		printf("prev final : key = %s, value = %s, next = %s\n",prev->key, prev->value, prev->next->key);
		i++;
	}
	return (0);
}
