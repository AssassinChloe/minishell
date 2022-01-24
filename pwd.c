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
int		ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(pwd);
	return (0);
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