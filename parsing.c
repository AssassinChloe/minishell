#include "minishell.h"

void    ft_parse(char *str)
{
    int i;
    char *command;

    i = 0;
    command = ft_calloc(1, sizeof(char));
    while(str[i])
    {
        while (str[i] && ft_isspace(str[i]) == 0 && ft_isquote(str[i]) == 0
        && ft_ispipe(str[i]) == 0)
        {    
            command = ft_strjoin_char(command, str[i]);
            i++;
        }
        printf("command: %s\n", command);
        free(command);
        return ;
        i++;
    }
}