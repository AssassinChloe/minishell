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

int	err_format_exit(char *str)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	g_data.exit_value = 2;
	g_data.loop = -1;
	return (2);
}

int	err_many_arg_exit(char *str)
{
	if (!check_format_exit(str))
		return (err_format_exit(str));
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	return (1);
}

int	init_exit(void)
{
	printf("exit\n");
	return (0);
}

int	ft_exit(t_cmd cmd)
{
	long long	number;

	number = init_exit();
	if (cmd.argc == 1)
		g_data.loop = -1;
	if (cmd.argc > 2)
		return (err_many_arg_exit(cmd.av[1]));
	if (cmd.argc == 2)
	{
		if (!check_format_exit(cmd.av[1]) || !ft_is_long_long(cmd.av[1]))
			g_data.exit_value = err_format_exit(cmd.av[1]);
		else
		{
			number = ft_atoll(cmd.av[1]);
			if (number < 0)
				while (number >= 0 && number <= 255)
					number = number + 256;
			if (number > 255)
				number = number % 256;
			g_data.exit_value = (int)number;
		}
		g_data.loop = -1;
		return ((int)number);
	}
	return (0);
}
