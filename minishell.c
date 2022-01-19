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
        if (buffer && buffer != NULL)
        {
          //  x = -1;
            printf("buffer : %s\n", buffer);
            free(buffer);
        }
    }
    printf("end \n");
    return (0);
}