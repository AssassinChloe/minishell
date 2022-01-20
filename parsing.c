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

int ft_isclosed(char *str, int i)
{
    char    c;
    
    c = str[i];
    i++;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

char    *ft_handleis(char *str, int *i)
{
    char *quote;
    int j;
    int ret;

    j = 0;
    if (ft_isspace(str[*i]) == 1)
    {
        while(str[*i] && ft_isspace(str[*i]) == 1)
            *i = *i + 1;
    }
    else if (ft_isdoublequote(str[*i]) == 1)
    {
        ret = ft_isclosed(str, *i);
        if (ret < 0)
        {
            *i = ret;
            printf("the double quote is not closed\n");
            return (NULL);
        }
        else
        {
            quote = malloc(sizeof(char) * (ret - *i) + 1);
            while (*i <= ret)
            {
                quote[j] = str[*i];
                j++;
                *i = *i + 1;
            }
            quote[j] = '\0';
        }
        printf("quote %s \n", quote);
        return (quote);
    }
    return (NULL);
}

void    ft_parse(char *str)
{
    int i;
    char *tmp;
    char *tmp2;
    t_list *tokens;
  
    i = 0;
    tmp = NULL;
    tokens = NULL;
    while(str[i])
    {
        while (str[i] && ft_isspace(str[i]) == 0 && ft_isquote(str[i]) == 0
        && ft_ispipe(str[i]) == 0)
        {    
            tmp = ft_strjoin_char(tmp, str[i]);
            i++;
        }
        if (tmp != NULL)
        {
            if (tokens == NULL)
                tokens = ft_lstnew(ft_strdup(tmp));
            else
                ft_lstadd_back(&tokens, ft_lstnew(ft_strdup(tmp)));
            if (tmp && *tmp)
            {
                free(tmp);
                tmp = NULL;
            }
        }
        if (str[i] && ft_isspace(str[i]) == 1 || ft_isquote(str[i]) == 1
        || ft_ispipe(str[i]) == 1)
        {
            tmp2 = ft_handleis(str, &i);
            if (tmp2 != NULL)
            {
                if (tokens == NULL)
                    tokens = ft_lstnew(ft_strdup(tmp2));
                else
                    ft_lstadd_back(&tokens, ft_lstnew(ft_strdup(tmp2)));
                free(tmp2);
            }
        }
    }
    ft_printchain(tokens);
    ft_lstclear(&tokens);
}