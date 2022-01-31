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

void    ft_divide_pipe(t_list * list, t_cmd **tmp, t_list **commandlist)
{
    t_list *tmplist;
    t_list *tmplist2;
    int     i;
    int     j;
    int     multicmd;
    
    tmplist = list;
    tmplist2 = list;
    while (tmplist)
    {
        multicmd = 0;
        i = 0;
        j = 0;
        *tmp = malloc(sizeof(t_cmd));
        while (tmplist && ft_strcmp((char*)tmplist->content, "|") != 0)
        {
            i++;
            tmplist = tmplist->next;
        }
        if (tmplist && ft_strcmp((char*)tmplist->content, "|") == 0)
            tmplist = tmplist->next;

        *tmp->argc = i;
        *tmp->argv = malloc(sizeof(char *) * (i + 1));
        *tmp->type = malloc(sizeof(int) * i);
        while (tmplist2 && i > j)
        {
            
            *tmp->argv[j] = ft_strdup((char *)tmplist2->content);
            *tmp->type[j] = get_token_type((char*)tmplist2->content, &multicmd);
            (if j > 0 && (*tmp->type[j - 1] >= T_LOWER && *tmp->type[j - 1] <= T_GGREATER))
                *tmp->type[j] = T_FILENAME;
            tmplist2 = tmplist2->next;
            j++;
        }
        *tmp->argv[j] = NULL;
        multicmd = 0;
        if (tmplist2 && ft_strcmp((char*)tmplist2->content, "|") == 0)
            tmplist2 = tmplist2->next;
        if (*commandlist == NULL)
            *commandlist = ft_lstnew(*tmp);
        else
            ft_lstadd_back(commandlist, ft_lstnew(*tmp));
    }
}

void ft_divide_redirection(list, t_cmd &tmp, &commandlist)
{

    
}
