/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:31:46 by vmercier          #+#    #+#             */
/*   Updated: 2022/03/10 12:32:22 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_data.execution == 0)
			rl_redisplay();
		g_data.exit_value = 130;
	}
	else if (sig == SIGQUIT && g_data.execution != 0)
	{
		write(1, "\b\b  \b\b", 6);
		printf("^\\Quit (core dumped)\n");
		g_data.exit_value = 131;
	}
	else
	{
		write(1, "\b\b  \b\b", 6);
	}
}

void	init_signal(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
}
