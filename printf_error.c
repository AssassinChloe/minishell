/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:50:01 by cassassi          #+#    #+#             */
/*   Updated: 2022/03/02 23:50:13 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_check_cmd(t_cmd *cmd, int *ret)
{
	if (cmd->env == 0)
	{
		if (*ret == 126) 
			printf("minishell: %s: Is a directory\n", cmd->av[0]);
		else if (*ret == 127)
			printf("minishell: %s: command not found\n", cmd->av[0]);
	}
	else
	{
		if (*ret > 0)
		{
			printf("env: %s: No such file or directory\n", cmd->av[0]);
			*ret = 127;
		}
	}

}

int	ft_is_only_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && ft_isdigit(str[i]) == 1)
		i++;
	if (str[i])
		return (0);
	return (1);
}
void	ft_print_error()
{
	char	*log;
	char	*error;
	int		ret;
	int     fd;

	if (g_data.nb_pipe > 0 && (fd = open(".log", O_RDONLY)) > 0)
	{ 
		log = NULL;
		error = NULL;
		ret = get_next_line(fd, &log);
		if (ret >= 0)
		{
		printf("test %s %d\n", log, g_data.exit_value);

			if (ft_is_only_digit(log) == 1)
				g_data.exit_value = ft_atoi(log);
			else 
				error = ft_strdup(log);
			while (ret == 1)
			{
				if (error != NULL)
					error = ft_strjoin(error, "\n");
				free(log);
				log = NULL;
				ret = get_next_line(fd, &log);
				if (ft_is_only_digit(log) == 1)
				{
					g_data.exit_value = ft_atoi(log);
					printf(" test2 exit %d\n", g_data.exit_value);
				}
				else 
					error = ft_strjoin(error, log);
			}
			if (ft_strlen(error) > 0)
			{
				write(STDERR_FILENO, error, (ft_strlen(error) + 1));
				g_data.exit_value = 1;
			}
			free(error);  
		}
		free(log);
		printf(" test3 exit %d\n", g_data.exit_value);
		log = NULL;
		close(fd);
		unlink(".log");
	}
}
