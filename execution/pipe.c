/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:28:00 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/14 10:37:05 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pipe(int **pip)
{
	int	i;

	i = 0;
	while (i < g_data.nb_pipe)
	{
		free(pip[i]);
		i++;
	}
	free(pip);
}

void	ft_open_pipes(int **pip)
{
	int	i;

	i = 0;
	while (i < g_data.nb_pipe)
	{
		pip[i] = malloc(sizeof(int) * 2);
		if (pipe(pip[i]) < 0)
			printf("error pipe\n");
		i++;
	}
}

void	ft_closepipe(int **pip)
{
	int	j;

	j = 0;
	while (j < g_data.nb_pipe)
	{
		if (close(pip[j][0]) < 0)
			printf("error close\n");
		if (close(pip[j][1]) < 0)
			printf("error close\n");
		j++;
	}
}

void	get_exit_val_pipe(int i)
{
	char	*nb;

	if (i == g_data.nb_pipe)
	{
		nb = ft_itoa(g_data.exit_value);
		write(2, nb, ft_strlen(nb));
		free(nb);
	}
}

void	handle_pipe(int i, int **pip)
{
	if (i < g_data.nb_pipe)
		dup2(pip[i][1], STDOUT_FILENO);
	if (i > 0)
		dup2(pip[i - 1][0], STDIN_FILENO);
	ft_closepipe(pip);
	if (i == g_data.nb_pipe)
		dup2(g_data.check, STDERR_FILENO);
}
