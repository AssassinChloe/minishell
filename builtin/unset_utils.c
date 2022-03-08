/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:37:17 by vmercier          #+#    #+#             */
/*   Updated: 2022/03/08 14:37:23 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
