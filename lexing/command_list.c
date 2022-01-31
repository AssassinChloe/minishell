#include "minishell.h"

void    ft_free_commandlist(t_list **commandlist)
{
    t_list *tmp;
    t_cmd   *type;
    int     i;

    tmp = *commandlist;
    while(tmp)
    {
        type = (t_cmd *)tmp->content;
        i = 0;
        while (i < type->argc)
        {
            free(type->argv[i]);
            i++;
        }
        free(type->argv);
        free(type->type);
        tmp = tmp->next;
    }
    ft_lstclear(commandlist);
}

void    ft_divide_pipe(t_list *tmplist, t_list *tmplist2, t_list **commandlist)
{
    int     i;
    int     j;
    int     multicmd;
    t_cmd	*tmp;
    
    while (tmplist)
    {
        multicmd = 0;
        i = 0;
        j = 0;
        tmp = malloc(sizeof(t_cmd));
        while (tmplist && ft_strcmp((char*)tmplist->content, "|") != 0)
        {
            i++;
            tmplist = tmplist->next;
        }
        if (tmplist && ft_strcmp((char*)tmplist->content, "|") == 0)
            tmplist = tmplist->next;

        tmp->argc = i;
        tmp->argv = malloc(sizeof(char *) * (i + 1));
        tmp->type = malloc(sizeof(int) * i);
        while (tmplist2 && i > j)
        {
            
            tmp->argv[j] = ft_strdup((char *)tmplist2->content);
            tmp->type[j] = get_token_type((char*)tmplist2->content, &multicmd);
            if (j > 0 && (tmp->type[j - 1] >= T_LOWER && tmp->type[j - 1] <= T_GGREATER))
                tmp->type[j] = T_FILENAME;
            tmplist2 = tmplist2->next;
            j++;
        }
        tmp->argv[j] = NULL;
        multicmd = 0;
        if (tmplist2 && ft_strcmp((char*)tmplist2->content, "|") == 0)
            tmplist2 = tmplist2->next;
        if (*commandlist == NULL)
            *commandlist = ft_lstnew(tmp);
        else
            ft_lstadd_back(commandlist, ft_lstnew(tmp));
    }
}

void ft_divide_redirection(t_list **commandlist)
{
    t_cmd *tmp;
    int i;
    int fd;
    int ret;
    int fdout;

    while (*commandlist)
    {
        i = 0;
        tmp = (t_cmd *)*commandlist->content;
        while (tmp->type[i] < T_LOWER || tmp->type[i] > T_GGREATER)
            i++;
        if (tmp->type[i] >= T_LOWER && tmp->type[i] <= T_GGREATER)
        {
            free(commandlist->content->argv[i]);
            commandlist->content->argv[i] = NULL;
        }
        if (tmp->type[i] == T_GREATER)
        {
            fd = open(tmp->argv[i + 1], O_CREATE|O_TRUNC, 0777);
            if (fd == -1)
            {
                printf("error open\n");
                return ;
            }
        }
        else if (tmp->type[i] == T_GGREATER)
        {
            fd = open(tmp->argv[i + 1], O_CREATE|O_APPEND, 0777);
            if (fd == -1)
            {
                printf("error open\n");
                return ;
            }
        }
        fdout = dup(STDOUT_FILENO);
        if (fdout == -1)
            printf("error copie stout\n");
        ret = dup2(fd, STDOUT_FILENO);
        if (ret == -1)
            printf("error redirection\n");
        ft_printtype(commandlist);
        ft_execution_test((t_cmd *)commandlist->content);
        ret = (STDOUT_FILENO, fdout);
        if (ret == -1)
            printf("error reestablish stdout\n");
        if (close(fdout) == -1 || close(fd) == -1)
            printf ("error close\n")
          
    }

    
}
