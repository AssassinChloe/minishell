#include "minishell.h"


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
        ret = ft_isclosed(str, *i);
        if (ret < 0)
        {
            *i = -1;
            printf("the quote is not closed\n");
            return (NULL);
        }
        else
        {
            j = 0;
            quote = malloc(sizeof(char) * (ret - *i) + 2);
            while (*i <= ret)
            {
                quote[j] = str[*i];
                j++;
                *i = *i + 1;
            }
            quote[j] = '\0';
        }
        return (quote);
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
    t_list *tokens;
    int keepgoing;
    int multiple;
  
    i = 0;
    tmp = NULL;
    tokens = NULL;
    keepgoing = 1;
    multiple = 0;
        while(str[i])
    {
        while (str[i] && ft_isspace(str[i]) == 0 && ft_isredir(str[i]) == 0 && ft_ispipe(str[i]) == 0 && keepgoing == 1)
        {
            multiple = 0;
            while (str[i] && ft_isspace(str[i]) == 0 && ft_isquote(str[i]) == 0
            && ft_ispipe(str[i]) == 0 && ft_isredir(str[i]) == 0)
            {   
                if (str[i] == ';' || str[i] == 92)
                {
                    printf("Error unsupported char\n");
                    if (tmp)
                        free(tmp);
                    if (tokens)
                        ft_lstclear(&tokens);
                    return ;
                }
                tmp = ft_strjoin_char(tmp, str[i]);
                i++;
            }
            if (str[i] && str[i + 1] && ft_isquote(str[i]) > 0)
            {
                if ((ft_isquote(str[i]) == 1 && ft_isquote(str[i + 1]) == 1)
                || (ft_isquote(str[i]) == 2 && ft_isquote(str[i + 1]) == 2))
                    i = i + 2;
                else
                    keepgoing = 0;
            }

        }
        ft_addone(&tokens, &tmp);
        keepgoing = 1;
        while (str[i] && ft_isspace(str[i]) == 1 || ft_isquote(str[i]) > 0
        || ft_ispipe(str[i]) == 1 || ft_isredir(str[i]) > 0)
        {
            tmp = ft_handleis(str, &i, &multiple);
            if (ft_isquote(str[i]) > 0)
                multiple = 0;
            if (tmp && tmp[0] == '"' && has_dollar(tmp) == 1)
            {
                ft_extract_var(&tokens, tmp);
                free(tmp);
            }
            else if (tmp == NULL && i < 0)
            {
                    if (tmp)
                        free(tmp);
                    if (tokens)
                        ft_lstclear(&tokens);
                    return ;
            }     
            else
                ft_addone(&tokens, &tmp);
        }
    }
    ft_printchain(tokens);
    ft_lstclear(&tokens);
}