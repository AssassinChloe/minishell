#include "minishell.h"

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t' || c == '\r')
        return (1);
    return (0);
}

int ft_isquote(char c)
{
    if (ft_issimplequote(c) == 1 || ft_isdoublequote(c) == 1)
        return (1);
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
        return (1);
    return (0);
}

int ft_ispipe(char c)
{
    if (c == '|')
        return (1);
    return (0);
}

