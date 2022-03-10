/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:30:02 by vmercier          #+#    #+#             */
/*   Updated: 2022/03/08 14:30:09 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_format_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_is_long_long(char *str)
{
	unsigned int		i;
	int					neg;
	unsigned long long	nb;

	i = 0;
	neg = 1;
	nb = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i++] - '0');
	}
	nb = (unsigned long long)nb;
	if (neg == -1 && nb > 9223372036854775808U)
		return (0);
	if (neg == 1 && nb > 9223372036854775807U)
		return (0);
	return (1);
}

void	destroy_var_env(t_env *var)
{
	if (var->key)
		free(var->key);
	if (var->value)
		free(var->value);
	free(var);
	var = NULL;
}

void	free_env(void)
{
	t_env	*tmp;
	t_env	*env;

	env = g_data.env;
	tmp = env;
	while (tmp != NULL)
	{
		env = env->next;
		destroy_var_env(tmp);
		tmp = env;
	}
	g_data.env = NULL;
}

void	free_g_data(void)
{
	if (g_data.env)
		free_env();
	if (g_data.line)
		free(g_data.line);
	if (g_data.env_in_tab)
		free_table_string(g_data.env_in_tab);
	if (g_data.log)
		free(g_data.log);
}
