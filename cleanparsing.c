#include "minishell.h"

void    ft_freeparsing(char **str, t_list **chain)
{
    free(*str);
    *str = NULL;
    ft_lstclear(chain);
}

int is_forbidden_char(char c)
{
    if (c == ';' || c == 92)
        return (1);
    return (0);
}