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

#include "minishell.h"
/*
fonction echo marche en prenant une serie d'args 
le premier arg[0] sera echo et ne sera pas ecrit
arg[1] peut etre -n ou pas
si le pflag peut etre inscrit plus loin dans les rgs, voir a deplacer
cette partie dan la boucle
voir pour les protections
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
static int	is_flag_n(char *arg)
{
	if (ft_strlen(arg) < 2)
		return (0);
	if (arg[0] == '-' || arg[1] == 'n')
		return (1);
	return (0);
}

int	ft_echo(char **args)
{
	int	flag_n;

	flag_n = 0;
	*args++; //si le premier arg est echo, on ne veut pa sl'imprimer
	if (is_flag_n(args[1])) // marche si le -n ne peut etre qu'au debut
	{
		flag_n = 1;
		*args++;
	}
	while (*args)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		if (*(++args))
		{
			ft_putchar_fd(' ', STDOUT_FILENO);
		}
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