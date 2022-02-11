#include "minishell.h"

void    ft_closepipe_end(int pip[g_data.nb_pipe][2], int i)
{
    if (i == 0)
    {
        if (close(pip[i][1]) < 0)
            printf("error close\n");
    }
    else if (i > 0 && i < g_data.nb_pipe)
    {
        if (close(pip[i - 1][0]) < 0)
            printf("error close\n");
        if (close(pip[i][1]) < 0)
            printf("error close\n");
    }
    else if (i == g_data.nb_pipe)
    {
        if (close(pip[i - 1][0]) < 0)
            printf("error close\n");
    }
}

void    ft_closepipe(int pip[g_data.nb_pipe][2], int i)
{
    int j;

    j = 0;
    if (i == 0)
    {
        while (j < g_data.nb_pipe)
        {
            if (close(pip[j][0]) < 0)
                printf("error close\n");
            if (j != i)
            {            
                if (close(pip[j][1]) < 0)
                    printf("error close\n");
            }
            j++;
        }
    }
    else if (i > 0 && i < g_data.nb_pipe)
    {
        while (j < g_data.nb_pipe)
        {
            if (j != (i - 1))
            {
                if (close(pip[j][0]) < 0)
                    printf("error close\n");
            }
            if (j != i)
            {           
                if (close(pip[j][1]) < 0)
                    printf("error close\n");
            }
            j++;
        }
    }
    else if (i == g_data.nb_pipe)
    {
        while (j < g_data.nb_pipe)
        {
            if (j != (i - 1))
            {
                if (close(pip[j][0]) < 0)
                    printf("error close\n");
            }            
            if (close(pip[j][1]) < 0)
                printf("error close\n");
            j++;
        }
    }
    else if (i > g_data.nb_pipe)
    {
        while (j < g_data.nb_pipe)
        {
            if (close(pip[j][0]) < 0)
                printf("error close\n");
            if (close(pip[j][1]) < 0)
                printf("error close\n");
            j++;
        }   
    }
}

void    ft_pipe(t_list *commandlist)
{
    int pid[g_data.nb_pipe + 1];
    t_cmd *command;
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
        ft_execution_test(command);
		if (command->redir_nb > 0)
			ft_endredir(command);
        return ;
    }
    else if (g_data.nb_pipe > 0)
    {
        while (i < g_data.nb_pipe)
        {
            if (pipe(pip[i]) < 0)
                printf("error pipe\n");
            i++;
        }
        i = 0;
        pid[i] = fork();
        if (pid[i] < 0)
            printf("error fork\n");
        while (pid[i] != 0 && (i + 1) <= g_data.nb_pipe)
        {
            i++;
            commandlist = commandlist->next;
            command = (t_cmd *)commandlist->content;
            pid[i] = fork();
        }
        if (pid[i] == 0)
        {  
            ft_closepipe(pip, i);
            ft_divide_redirection(commandlist);
            if (i < g_data.nb_pipe)
                dup2(pip[i][1], STDOUT_FILENO);
            if (i > 0)
                dup2(pip[i - 1][0], STDIN_FILENO);
            ft_execution_test(command);
            		if (command->redir_nb > 0)
			ft_endredir(command);
            ft_closepipe_end(pip, i);
            exit(EXIT_SUCCESS);
        }
        else
        {
            ft_closepipe(pip, (i + 1));
            while (wait(NULL) != -1 || errno != ECHILD)
            {
                j++;
            }
        }
    }
    return ;
}