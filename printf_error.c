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

void	check_log(char **log, char **error)
{
	if (g_data.nb_pipe > 0 && ft_is_only_digit(*log) == 1)
				g_data.exit_value = ft_atoi(*log);
	else
		*error = ft_strjoin(*error, *log);
}

void	handle_error(char **error)
{
	if (ft_strlen(*error) > 0)
	{
		if (ft_strlen(*error) > 20
			&& (ft_strncmp("/usr/bin/ls: cannot access", *error, 20) == 0
				|| ft_strncmp("/bin/ls: cannot access", *error, 20) == 0))
			g_data.exit_value = 2;
		else
			g_data.exit_value = 1;
		write(STDERR_FILENO, *error, (ft_strlen(*error) + 1));
	}
	free(*error);
}

void	end_gnl_struct(t_gnl *gnl)
{
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
		handle_error(&error);
	}
	end_gnl_struct(&gnl);
}
