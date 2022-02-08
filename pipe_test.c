#include "minishell.h"

void    ft_pipe(t_list *commandlist)
{
    int pid;
    t_cmd *command;
    int fd_in;
    int fd_out;
    int		status = 0;
    int     pip[g_data.nb_pipe][2];
    int     savestd[2];
    int     i;
    int     j;

    savestd[0] = dup(STDIN_FILENO);
    savestd[1] = dup(STDOUT_FILENO);
    i = 0;
    j = 0;
    command = (t_cmd *)commandlist->content;
    if (g_data.nb_pipe == 0)
    {
        ft_divide_redirection(commandlist);
        return ;
    }
    else if (g_data.nb_pipe > 0)
    {
        while (j <= g_data.nb_pipe && commandlist)
        {

            command = (t_cmd *)commandlist->content;
            if (i > 0)
                pid = fork();
            else if (i == 0)
            {
                if (pipe(pip[i]) < 0)
                    printf("error pipe\n");
                pid = fork();
            }
            if (pid < 0)
                printf("error fork\n");
            if (pid == 0)
            {  
                printf("child test plop\n");     

                fd_out = pip[i][1];
                if (i > 0)
                {
                    fd_in = pip[i - 1][0];
                    dup2(fd_in, STDIN_FILENO);
                }
                if (commandlist->next == NULL)
                {
                    if (dup2(savestd[1], STDOUT_FILENO) == -1)
                        printf("error reestablish stdout\n");
                }
                else
                {
                    if (dup2(fd_out, STDOUT_FILENO) == -1)
                        printf("errror chnging stdout\n");
                }

                ft_execution_test(command);

                if (close(pip[i][1]) == -1)
                    printf ("error close\n");               
                if (close(pip[i][0]) == -1)
                    printf ("error close\n");
                printf("end child test plop\n");
                if (command->next == NULL)
                {
                    if (dup2(savestd[0], STDIN_FILENO) == -1)
                        printf("error reestablish stdin\n");
                    if (dup2(savestd[1], STDOUT_FILENO) == -1)
                        printf("error reestablish stdout\n");
                }
                exit(EXIT_SUCCESS);
            }
            else
            {
                waitpid(pid, &status, 0);
                printf("end waiting\n");
                commandlist = commandlist->next;
                if (commandlist)
                {
                if (commandlist->next != NULL)
                {
                    if (pipe(pip[i + 1]) < 0)
                        printf("error pipe\n");
                    fd_out = pip[i + 1][1];
                    dup2(fd_out, STDOUT_FILENO);
                } 
                command = (t_cmd *)commandlist->content;  
                fd_in = pip[i][0];
                dup2(fd_in, STDIN_FILENO);
                if (commandlist->next == NULL)
                {
                    if (dup2(savestd[1], STDOUT_FILENO) == -1)
                        printf("error reestablish stdout\n");
                }
                ft_execution_test(command);
                }
                if (close(pip[i][0]) == -1)
                    printf("error close\n");
                if (close(pip[i][1]) == -1)
                    printf ("error close\n");
                               if (command->next == NULL)
                {
                    if (dup2(savestd[0], STDIN_FILENO) == -1)
                        printf("error reestablish stdin\n");
                    if (dup2(savestd[1], STDOUT_FILENO) == -1)
                        printf("error reestablish stdout\n");
                }     
            }
    
            printf("parent test plop\n");

            i++;
            j = j + 2;
            if (commandlist)
                commandlist = commandlist->next;
        }

    }
    return ;
}