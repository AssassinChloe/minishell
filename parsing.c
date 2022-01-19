#include "minishell.h"

void    ft_parse(char *str)
{
    int i;
    char *tmp;
    t_list *tokens;
  
    i = 0;
    tmp = ft_calloc(1, sizeof(char));
    while(str[i])
    {
        while (str[i] && ft_isspace(str[i]) == 0 && ft_isquote(str[i]) == 0
        && ft_ispipe(str[i]) == 0)
        {    
            tmp = ft_strjoin_char(tmp, str[i]);
            i++;
        }
        if (!tokens)
            tokens = ft_lstnew(tmp);
        else
            ft_lstadd_back(&tokens, ft_lstnew(tmp));

        printf("command: %s\n", tmp);
        free(tmp);
        tmp = NULL;
        i++;   
    }
}