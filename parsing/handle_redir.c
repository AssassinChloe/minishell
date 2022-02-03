#include "minishell.h"

int ft_isredir(char c, char *str, int i)
{
    if (c == '<')
        return (1);
    else if (c == '>')
        return (2);
    else if (ft_isdigit(c) == 1)
    {
        while (str[i] && ft_isspace(str[i]) == 0)
        {
            if (str[i] == '<' || str[i] == '>')
                return(3);
        }
        i++;
    }
    return (0);
}

int ft_isdoubleredir(char *str, int i)
{
    int ret;

    ret = ft_isredir(str[i], str, i);
    if (ret == 3)
        return (ret);
    if (ret < 3 && str[i + 1])
    {
        if (ft_isredir(str[i + 1], str, i) == 0)
            return (0);
        else
        {
            if (ft_isredir(str[i + 1], str, i) == ret)
                return (1);
            else
                return (-1);
        }
    }
    return (0);
}