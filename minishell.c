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
	g_data.split = NULL;
	g_data.env = get_env(envp);
	g_data.env_in_tab = ft_env_in_tab();
	g_data.exit_value = 0;
	g_data.nb_pipe = 0;
	g_data.execution = 0;
	g_data.token = 0;
	g_data.log = ft_strjoin(get_env_value("HOME"), "/.log");
}

void	end_one(void)
{
	ft_print_error();
	unlink(g_data.log);
	unlink(".heredoc");
	g_data.nb_pipe = 0;
	g_data.token = 0;
	ft_free_splitlist(&g_data.split);
	g_data.split = NULL;
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
				end_one();
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
	g_data.env_in_tab = ft_env_in_tab();
	init_signal();
	minishell();
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	return (g_data.exit_value);
}
