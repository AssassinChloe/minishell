#include "minishell.h"

void    ft_child_action(int pip[g_data.nb_pipe][2], int i, t_list *commandlist, t_cmd *command)
{
                ft_closepipe(pip, i);
            ft_divide_redirection(commandlist);
            if (i < g_data.nb_pipe)
                dup2(pip[i][1], STDOUT_FILENO);
            if (i > 0)
                dup2(pip[i - 1][0], STDIN_FILENO);
            ft_get_cmd_path(command);
            		if (command->redir_nb > 0)
			ft_endredir(command);
            ft_closepipe_end(pip, i);
            exit(EXIT_SUCCESS);
}

void    ft_open_pipes(int pip[g_data.nb_pipe][2])
{
    int i;

    i = 0;
    while (i < g_data.nb_pipe)
        {
            if (pipe(pip[i]) < 0)
                printf("error pipe\n");
            i++;
        }
}

void    ft_pipe(t_list *commandlist)
{
    int pid;
    t_cmd *command;
    int     pip[g_data.nb_pipe][2];
    int     i;

    i = 0;
    command = (t_cmd *)commandlist->content;
    ft_open_pipes(pip);    
        pid = fork();
        if (pid < 0)
            printf("error fork\n");
        while (pid != 0 && (i + 1) <= g_data.nb_pipe)
        {
            i++;
            commandlist = commandlist->next;
            command = (t_cmd *)commandlist->content;
            pid = fork();
        }
        if (pid == 0)
            ft_child_action(pip, i, commandlist, command);
        else
        {
            ft_closepipe(pip, (i + 1));
            while (wait(NULL) != -1 || errno != ECHILD);
        }
    return ;
}