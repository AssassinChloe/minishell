#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include "minishell.h"

t_data	g_data;

void    handle_sig(int sig)
{
//(void)g_data;
if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_data.execution == 0)
			rl_redisplay();
		g_data.exit_value = 130;
	}
if (sig == SIGQUIT)
{
	write(1, "\b\b  \b\b", 6);
	g_data.exit_value = 131;
}
}
/*
t_env	*get_env(char **envp)
{
	
}
*/
void	init_data(char **envp)
{
	g_data.loop = 1;
	g_data.line = NULL;
	g_data.env = NULL; //get_env(envp);
	g_data.export_env = NULL; //get_env(envp);
	g_data.exit_value = 0;
	g_data.cmd_lst = NULL;
	g_data.nb_pipe = 0;
	g_data.execution = 0;
}

void	init_signal()
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);

}

int minishell()
{
	char	*buffer;
	int		buffer_size;
	

	while (g_data.loop > 0) // remplacement de x = 1
	{
		init_signal();
		buffer = readline("$> ");
		if (buffer)
		{
			printf("buffer : %s\n", buffer);
			if (*buffer)
				add_history(buffer);
 			ft_parse(buffer);
			free(buffer);
		}
		else
		{
			g_data.loop = -1;
		}
	}
	printf("end \n");
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		exit(EXIT_FAILURE);
	init_data(envp);
	init_signal();
	minishell();
//	ft_free_all(); a faire
	return (0);
}