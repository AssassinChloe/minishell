#include "minishell.h"

int ft_isquote(char c)
{
    if (ft_issimplequote(c) == 1)
        return (1);
    else if (ft_isdoublequote(c) == 2)
        return (2);
    return (0);
}

int ft_issimplequote(char c)
{
    if (c == 39)
        return (1);
    return (0);
}

int ft_isdoublequote(char c)
{
    if (c == 34)
        return (2);
    return (0);
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

char    *ft_handle_quote(char *str, int *i, int keepquote)
{
    int ret;
    int j;
    char *quote;

    quote = NULL;
    ret = ft_isclosed(str, *i);
    if (ret < 0)
    {
        *i = -1;
        printf("the quote is not closed\n");
        return (NULL);
    }
    else
    {
        if (keepquote == 0)
        {
            *i = *i + 1;
            ret--;
        }
        j = 0;
        quote = malloc(sizeof(char) * (ret - *i) + 2);
        while (*i <= ret)
        {
            quote[j] = str[*i];
            j++;
            *i = *i + 1;
        }
        quote[j] = '\0';
        if (keepquote == 0)
            *i = *i + 1;
    }
    return (quote);
}