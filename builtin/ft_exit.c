/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:47:37 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/16 13:47:45 by vmercier         ###   ########.fr       */
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
}

int	err_format_exit(char *str)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	g_data.exit_value = 2;
	return (2);
}

int	ft_exit(t_cmd cmd)
{
	int	number;

	if (cmd.argc == 1)
		g_data.loop = -1;
	if (cmd.argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (cmd.argc == 2)
	{
		if (!check_format_exit(cmd.av[1]))
			return (err_format_exit(cmd.av[1]));
		number = ft_atoi(cmd.av[1]);
		if (number < 0)
		{
			while (number >= 0 && number <= 255)
				number = number + 256;
		}
		if (number > 255)
			number = number % 256;
		g_data.loop = -1;
		return (number);
	}
	return (0);
}
