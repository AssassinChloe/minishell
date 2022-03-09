/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:10:14 by vmercier          #+#    #+#             */
/*   Updated: 2022/01/24 13:11:06 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
/*
fonction echo marche en prenant une serie d'args 
le premier arg[0] sera echo et ne sera pas ecrit
les premiers args peuvent etre -n ou -nnnnn ou pas

voir pour les protections
voir pour mise a jour de g_data.exit_value
*/

int	is_flag_n(char *arg)
{
	int	i;

	i = 0;
	if (ft_strlen(arg) < 2)
	{
		return (0);
	}
	if (arg[0] != '-')
		return (0);
	else
	{
		i++;
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
}

int	ft_echo(char **args)
{
	int	flag_n;
	int	i;

	flag_n = 0;
	i = 1;
	g_data.exit_value = 0;
	while (is_flag_n(args[i]))
	{
		flag_n = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[++i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flag_n == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
