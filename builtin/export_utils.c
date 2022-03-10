/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:22:37 by vmercier          #+#    #+#             */
/*   Updated: 2022/03/10 12:22:43 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_equal(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	has_plus_equal(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i + 1])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	count_var_env(void)
{
	int		nb_var;
	t_env	*var;

	var = g_data.env;
	nb_var = 0;
	while (var->next)
	{
		nb_var++;
		var = var->next;
	}
	return (nb_var);
}

char	**table_export_key(void)
{
	char	**table;
	int		nb_var;
	t_env	*var;

	var = g_data.env;
	nb_var = count_var_env();
	table = (char **)malloc(sizeof(char *) * (nb_var + 2));
	if (!table)
		return (NULL);
	var = g_data.env;
	table[nb_var + 1] = NULL;
	while (var->next)
	{
		table[nb_var] = ft_strdup(var->key);
		nb_var--;
		var = var->next;
	}
	table[nb_var] = ft_strdup(var->key);
	return (table);
}

char	**sort_table(char **table)
{
	int		i;
	int		j;
	char	*tmp;

	if (*table == NULL)
		return (NULL);
	i = 0;
	while (table[i])
	{
		j = i;
		while (j && ft_strcmp(table[j], table[j - 1]) < 0)
		{
			tmp = table[j];
			table[j] = table[j - 1];
			table[j - 1] = tmp;
			j--;
		}
		i++;
	}
	return (table);
}
