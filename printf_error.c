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

int	ft_is_only_digit(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0)
		return (0);
	while (str[i] && ft_isdigit(str[i]) == 1)
		i++;
	if (str[i])
		return (0);
	return (1);
}

void	identify_error(char *error)
{
	if (ft_strcmp(error, "minishell: No such file or directory") == 0)
		g_data.exit_value = 127;
	else if (ft_strlen(error) > 16
		&& (ft_strncmp("/usr/bin/ls: can", error, 16) == 0
			|| ft_strncmp("/bin/ls: can", error, 11) == 0))
		g_data.exit_value = 2;
	else if (g_data.exit_value == 0)
		g_data.exit_value = 1;
}

void	check_log(char **log, char **error)
{
	if (ft_is_only_digit(*log) == 1)
		g_data.exit_value = ft_atoi(*log);
	else if (ft_strcmp(*log, "") != 0)
	{
		identify_error(*log);
		*error = ft_strjoin(*error, *log);
	}
}

void	print_and_end(t_gnl *gnl, char **error)
{
	if (gnl->ret >= 0 && ft_strlen(*error) > 0)
		write(STDERR_FILENO, *error, (ft_strlen(*error) + 1));
	free(*error);
	free(gnl->log);
	gnl->log = NULL;
	close(gnl->fd);
}

void	ft_print_error(void)
{
	t_gnl	gnl;
	char	*error;

	gnl.fd = open(g_data.log, O_RDONLY);
	if (gnl.fd < 0)
		return ;
	gnl.log = NULL;
	error = NULL;
	gnl.ret = get_next_line(gnl.fd, &gnl.log);
	if (gnl.ret >= 0)
	{
		check_log(&gnl.log, &error);
		while (gnl.ret == 1)
		{
			if (error != NULL)
				error = ft_strjoin(error, "\n");
			free(gnl.log);
			gnl.log = NULL;
			gnl.ret = get_next_line(gnl.fd, &gnl.log);
			check_log(&gnl.log, &error);
		}
	}
	print_and_end(&gnl, &error);
}
