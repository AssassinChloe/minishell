#include "minishell.h"

int main()
{
    char    *buffer;
    int     buffer_size;
    int x;

    x = 1;
    while (x > 0)
    {
        buffer = readline("$> ");
        if (buffer && ft_strcmp("exit", buffer) != 0)
        {
            if (*buffer)
                add_history(buffer);
            ft_parse(buffer);
            free(buffer);
        }
        else
        {
            x = -1;
            rl_clear_history();
        }
    }
    printf("end \n");
    return (0);
}
