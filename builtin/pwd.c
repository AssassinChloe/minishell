/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:53:36 by vmercier          #+#    #+#             */
/*   Updated: 2022/01/24 12:58:05 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
int	ft_pwd(t_cmd cmd)
{
	char	*pwd;

	if (cmd.av[1] && cmd.av[1][0] == '-' && cmd.av[1][1])
	{
		ft_putstr_fd("minshell: pwd: ", 2);
		ft_putchar_fd(cmd.av[1][0], 2);
		ft_putchar_fd(cmd.av[1][1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		g_data.exit_value = 2;
		return (2);
	}
	else
	{
		pwd = getcwd(NULL, 0);
		ft_putstr_fd(pwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(pwd);
		return (0);	
	}
}
/*
int	main()
{
    char *env1="PWD";
	char *env2="PATH";
    char *env3="USER";

    ft_pwd();
	printf("value de %s : %s\n", env1, getenv(env1));
    printf("value de %s : %s\n", env2, getenv(env2));
    printf("value de %s : %s\n", env3, getenv(env3));

	return (0);
}
*/