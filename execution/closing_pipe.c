/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:38:35 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/13 23:41:48 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_first(int pip[g_data.nb_pipe][2], int i)
{
	int	j;

	j = 0;
	while (j < g_data.nb_pipe)
	{
		if (close(pip[j][0]) < 0)
			printf("error close\n");
		if (j != i)
		{
			if (close(pip[j][1]) < 0)
				printf("error close\n");
		}
		j++;
	}
}

void	ft_close_middle(int pip[g_data.nb_pipe][2], int i)
{
	int	j;

	j = 0;
	while (j < g_data.nb_pipe)
	{
		if (j != (i - 1))
		{
			if (close(pip[j][0]) < 0)
				printf("error close\n");
		}
		if (j != i)
		{
			if (close(pip[j][1]) < 0)
				printf("error close\n");
		}
		j++;
	}
}

void	ft_close_last(int pip[g_data.nb_pipe][2], int i)
{
	int	j;

	j = 0;
	while (j < g_data.nb_pipe)
	{
		if (j != (i - 1))
		{
			if (close(pip[j][0]) < 0)
				printf("error close\n");
		}
		if (close(pip[j][1]) < 0)
			printf("error close\n");
		j++;
	}
}

void	ft_closepipe_end(int pip[g_data.nb_pipe][2], int i)
{
	if (i == 0)
	{
		if (close(pip[i][1]) < 0)
			printf("error close\n");
	}
	else if (i > 0 && i < g_data.nb_pipe)
	{
		if (close(pip[i - 1][0]) < 0)
			printf("error close\n");
		if (close(pip[i][1]) < 0)
			printf("error close\n");
	}
	else if (i == g_data.nb_pipe)
	{
		if (close(pip[i - 1][0]) < 0)
			printf("error close\n");
	}
}

void	ft_closepipe(int pip[g_data.nb_pipe][2], int i)
{
	int	j;

	j = 0;
	if (i == 0)
		ft_close_first(pip, i);
	else if (i > 0 && i < g_data.nb_pipe)
		ft_close_middle(pip, i);
	else if (i == g_data.nb_pipe)
		ft_close_last(pip, i);
	else if (i > g_data.nb_pipe)
	{
		while (j < g_data.nb_pipe)
		{
			if (close(pip[j][0]) < 0)
				printf("error close\n");
			if (close(pip[j][1]) < 0)
				printf("error close\n");
			j++;
		}
	}
}
