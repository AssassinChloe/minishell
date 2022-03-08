/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:31:49 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/17 16:31:56 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	init_data(char **envp)
{
	g_data.loop = 1;
	g_data.line = NULL;
	g_data.split = NULL;
	g_data.env = get_env(envp);
	g_data.exit_value = 0;
	g_data.cmd_lst = NULL;
	g_data.nb_pipe = 0;
	g_data.execution = 0;
	g_data.token = 0;
}

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

int	minishell(void)
{
	char	*buffer;

	while (g_data.loop > 0)
	{
		buffer = readline("$> ");
		if (buffer)
		{
			if (*buffer)
			{
				add_history(buffer);
				ft_parse(buffer);
				ft_print_error();
				unlink(".heredoc");
				g_data.nb_pipe = 0;
				g_data.token = 0;
				ft_lstclear(&g_data.split);
				g_data.split = NULL;
			}
			free(buffer);
			buffer = NULL;
		}
		else
			g_data.loop = -1;
	}
	rl_clear_history();
	free_g_data();
	printf("exit\n");
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	init_data(envp);
	modify_shlvl_value();
	init_signal();
	minishell();
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	return (g_data.exit_value);
}
