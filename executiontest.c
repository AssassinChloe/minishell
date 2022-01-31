#include "minishell.h"

void	exec_cmd(char **cmd)
{
	pid_t	pid = 0;
	int		status = 0;

	// On fork
	pid = fork();
	if (pid == -1)
		perror("fork");
	// Si le fork a reussit, le processus pere attend l'enfant (process fork)
	else if (pid > 0) {
		// On block le processus parent jusqu a ce que l'enfant termine puis
		// on kill le processus enfant
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	} else {
		// Le processus enfant execute la commande ou exit si execve echoue
		if (execve(cmd[0], cmd, NULL) == -1)
			perror("shell");
		exit(EXIT_FAILURE);
	}
}

void ft_execution_test(t_cmd *cmd)
{
    char *path;
    char *bin;
    char **path_split;
    int     i;
    int     j;

    i = 0;
    j = 0;
    bin = NULL;
    if (access(cmd->argv[0], F_OK) != 0)
    {
        path = getenv("PATH");
        path_split = ft_split(path, ":");
        while (path_split[i])
            i++;
        bin = ft_strdup(path_split[j]);
        bin = ft_strjoin(bin, "/");
        bin = ft_strjoin(bin, cmd->argv[0]);
        if (!bin)
            printf("error malloc\n");
        while (j < i && access(bin, F_OK != 0))
        {
            free(bin);
            bin = NULL;
            j++;
            if (j < i)
            {
            bin = ft_strdup(path_split[j]);
            bin = ft_strjoin(bin, "/");
            bin = ft_strjoin(bin, cmd->argv[0]);
            if (!bin)
                printf("error malloc\n");
            }
        }
    }
    free(cmd->argv[0]);
    cmd->argv[0] = ft_strdup(bin);
    printf("path to binaire : %s\n", cmd->argv[0]);
    free(bin);
    i = 0;
    while (path_split[i])
    {
        free(path_split[i]);
        i++;
    }
    exec_cmd(cmd->argv);
}