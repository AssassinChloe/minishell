#include "minishell.h"

int ft_countredir(t_cmd *cmd)
{
    int i;
    int ret;

    i = 0;
    ret = 0;
    while (i < cmd->argc)
    {
        if (cmd->type[i] >= T_LOWER && cmd->type[i] <= T_GGREATER)
        {
            ret++;
        }
        i++;
    }
    return (ret);
}