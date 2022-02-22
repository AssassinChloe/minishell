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
