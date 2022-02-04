#include "minishell.h"

int ft_isredir(char c)
{
    if (c == '<')
        return (1);
    else if (c == '>')
        return (2);
    return (0);
}

int ft_isdoubleredir(char *str, int i)
{
    int ret;

    ret = ft_isredir(str[i]);
    if (str[i + 1])
    {
        if (ft_isredir(str[i + 1]) == 0)
            return (0);
        else
        {
            if (ft_isredir(str[i + 1]) == ret)
                return (1);
            else
                return (-1);
        }
    }
    return (0);
}