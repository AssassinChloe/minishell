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

// intcheckemptyquote()
// {

// }
// char *extract_quote(char)
// {

// }