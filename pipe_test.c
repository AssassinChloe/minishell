#include "minishell.h"

void    ft_pipe(t_list *commandlist)
{
    int id;
    t_cmd *command;
    t_redir *tuyau;
    int i;

    i = 0;
    command = (t_cmd *)commandlist->content;
    tuyau = malloc(sizeof(t_redir));
    if (g_data.nb_pipe == 0)
    {
        ft_divide_redirection(commandlist);
        return ;
    }
    else 
    {
        if (pipe(command->pip) < 0)
            printf("error pipe\n");
        id = fork();
        if (id == 0)
        {
            if (close(command->pip[0]) == -1)
                printf ("error close\n");
            tuyau->fd = command->pip[0];
            commandlist = commandlist->next;
            command = (t_cmd *)commandlist->content;
            i++;
            ft_divide_redirection(commandlist);
            if (command->redir_nb > 0)
                ft_redirstd(tuyau, command->redir->fd);
            else
                ft_redirstd(tuyau, STDOUT_FILENO);
            ft_execution_test(command);
            if (dup2(tuyau->fdsave, STDOUT_FILENO) == -1)
                printf("error reestablish stdout\n");
            if (command->redir_nb > 0)
                ft_endredir(command);
            if (close(command->pip[1]) == -1)
                printf ("error close\n");
        }
        else 
        {
            if (close(command->pip[1]) == -1)
                printf ("error close\n");
            tuyau->fd = command->pip[1];
            ft_divide_redirection(commandlist);
            if (command->redir_nb > 0)
                ft_redirstd(tuyau, command->redir->fd);
            else
                ft_redirstd(tuyau, STDIN_FILENO);
            ft_execution_test(command);
            if (dup2(tuyau->fdsave, STDIN_FILENO) == -1)
                printf("error reestablish stdout\n");
            if (command->redir_nb > 0)
                ft_endredir(command);
            if (close(command->pip[0]) == -1)
                printf ("error close\n");
        }
        free(tuyau);
        tuyau = NULL;
    }
    return ;
}