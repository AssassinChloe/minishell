#include "minishell.h"

void    ft_printchain(t_list *elem)
{
    t_list  *tmp;
    int i;

    i = 0;
    tmp = elem;
    while (tmp)
    {
        printf("token %d : %s\n", i, (char *)tmp->content);
        tmp = tmp->next;
        i++;
    }
}

void    ft_addone(t_list **tokens, char *tmp)
{
    if (tmp != NULL)
    {
        if (*tokens == NULL)
            *tokens = ft_lstnew(ft_strdup(tmp));
        else
            ft_lstadd_back(tokens, ft_lstnew(ft_strdup(tmp)));
        free(tmp);
        tmp = NULL;
    }
}