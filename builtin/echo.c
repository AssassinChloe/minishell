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

/*
size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n] != '\0')
		n++;
	return (n);
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t		i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i])
		i++;
	write(fd, s, i);
}
*/
int	is_flag_n(char *arg) // modifie pour integer les nnn possibles
{
	int i;

	i = 0;
	if (ft_strlen(arg) < 2)
		return (0);
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
	int i;

	flag_n = 0;
	i = 1; //le premier arg est echo, on ne veut pas l'imprimer
	while (is_flag_n(args[i])) // le -n ne peut etre qu'au debut, sur n args
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
/*
int	main(int argc, char **argv)
{
	printf("flag -n ? %d\n", is_flag_n(argv[1]));
	ft_echo(argv);

	return (0);
}
*/