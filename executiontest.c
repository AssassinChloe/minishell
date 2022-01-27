#include "minishell.h"

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
    cmd->argv[0] = ft_strdup(bin);
    if(execve(cmd->argv[0], cmd->argv, NULL) == -1)
        perror("shell");
}