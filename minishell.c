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

void	destroy_var(t_env *var)
{
	if (var->key)
		free(var->key);
	if (var->value)
		free(var->value);
	free(var);
}

void	clear_list(t_env **list)
{
	t_env	*var;
	t_env	*tmp;

	if (!list || !(*list))
		return ;
	var = *list;
	while (var)
	{
		tmp = var;
		var = var->next;
		destroy_var(tmp);
	}
	*list = NULL;
}

t_env	*record_var(char *key, char *value)
{
	t_env	*var;

	var = (void *)malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	var->has_value = 1;
	if (!value)
		var->has_value = 0;
	var->next = NULL;
	if (!var->key || !var->value)
	{
		destroy_var(var);
		var = NULL;
	}
	return (var);
}

t_env	*get_env(char **envp)
{
	t_env	*var_env;
	t_env	*var;
	char	**tmp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	var_env = NULL;
	while (i--)
	{
		tmp = ft_split_env(envp[i]);
		var = record_var(tmp[0], tmp[1]);
		if (!var)
		{
			free_tab2(tmp);
			clear_list(&var_env);
			break ;
		}
		var->next = var_env;
		var_env = var;
		free_tab2(tmp);
	}
	return (var_env);
}

void	init_data(char **envp)
{
	g_data.loop = 1;
	g_data.line = NULL;
	g_data.env = get_env(envp);
	g_data.exit_value = 0;
	g_data.cmd_lst = NULL;
	g_data.nb_pipe = 0;
	g_data.execution = 0;
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
				printf("plop\n");
				unlink(".heredoc");
				g_data.nb_pipe = 0;
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
	return (0);
}
