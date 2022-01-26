#include "minishell.h"

char    *ft_handleis(char *str, int *i, int *multiple)
{
    char *quote;
    int j;
    int ret;
 
    if (ft_isspace(str[*i]) == 1)
    {
        while(str[*i] && ft_isspace(str[*i]) == 1)
            *i = *i + 1;
    }
    else if (ft_isdoublequote(str[*i]) == 2 || ft_issimplequote(str[*i]) == 1)
    {
        *multiple = 0;
        return (ft_handle_quote(str, i, 1));
    }
    else if (ft_ispipe(str[*i]) == 1)
    {
        if (*multiple == 0)
        {
            *multiple = 1;
            quote = malloc(sizeof(char) * 2);
            quote[0] = str[*i];
            quote[1] = '\0';
            *i = *i + 1;
            return (quote);
        }
        else
        {
            *i = -1;
            printf("error multiple specific char without arg between\n");
            *multiple = 0;
            return (NULL);
        }
    }
    else if (ft_isredir(str[*i]) > 0)
    {
        if (*multiple == 0)
        {

            *multiple = 1;
            ret = ft_isdoubleredir(str, *i);
            if (ret == 1)
            {
                quote = malloc(sizeof(char) * 3);
                j = 0;
                while (j < 2)
                {
                    quote[j] = str[*i];
                    j++;
                    *i = *i + 1;
                }
                quote[j] = '\0';
                return (quote);
            }
            else if (ret == 0)
            {
                quote = malloc(sizeof(char) * 2);
                quote[0] = str[*i];
                quote[1] = '\0';
                *i = *i + 1;
                return (quote);
            }
            else
            {
                *i = -1;
                printf("error multiple specific char without arg between\n");
                *multiple = 0;
                return (NULL);
            }
        }
        else
            {
                *i = -1;
                printf("error multiple specific char without arg between\n");
                *multiple = 0;
                return (NULL);
            }
    }
    return (NULL);
}

void    ft_parse(char *str)
{
    int i;
    char *tmp;
    char *tmp2;
    int ret;
    t_list *tokens;
    int multiple;
  
    i = 0;
    tmp = NULL;
    tmp2 = NULL;
    tokens = NULL;
    multiple = 0;
    while(str[i])
    {
        while (str[i] && ft_isspace(str[i]) == 0 && ft_isredir(str[i]) == 0 && ft_ispipe(str[i]) == 0)
        {
            multiple = 0;
            while (str[i] && ft_isspace(str[i]) == 0 && ft_isquote(str[i]) == 0
            && ft_ispipe(str[i]) == 0 && ft_isredir(str[i]) == 0)
            {   
                if (is_forbidden_char(str[i]) == 1)
                    return (ft_freeparsing(&tmp, &tokens));    
                tmp = ft_strjoin_char(tmp, str[i]);
                i++;
            }
            if (has_dollar(tmp) == 1)
                tmp = ft_extract_var(tmp);
            if (str[i] && ft_isquote(str[i]) > 0)
            {
                ret = ft_isquote(str[i]);
                tmp2 = ft_handle_quote(str, &i, 0), 0;
                if (tmp2 == NULL && i < 0)
                {
                    ft_freeparsing(&tmp, &tokens);
                    return ;
                }
                if (ret == 2 && has_dollar(tmp2) == 1)
                    tmp2 = ft_extract_var(tmp2);
                if (tmp != NULL)
                    tmp = ft_strjoin(tmp, tmp2);
                else
                    tmp = ft_strdup(tmp2);
                free(tmp2);
            }
        }
        ft_addone(&tokens, &tmp);
        while (str[i] && ft_isspace(str[i]) == 1 || ft_ispipe(str[i]) == 1 || ft_isredir(str[i]) > 0)
        {
            tmp = ft_handleis(str, &i, &multiple);
            if (tmp == NULL && i < 0)
            {
                    ft_freeparsing(&tmp, &tokens);
                    return ;
            }     
            else
                ft_addone(&tokens, &tmp);
        }
    }
    ft_printchain(tokens);
    ft_lstclear(&tokens);
}