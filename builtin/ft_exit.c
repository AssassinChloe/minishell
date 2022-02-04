/*

#include "minishell.h"

int ft_exit(t_cmd cmd)
{
    if (cmd->argc == 1)
    {
//        destroy(); //mettre en parametre g_data.exit_value?
    }
    if (cmd->argc > 2)
    {
        ft_print_error(" wrong arguments")
    }
    if (cmd->argc == 2)
    {
        ft_atoi(cmd->argv[1]) // voir pour adapter atoi ?
        //si resultat <0 ou sup > 255 error "wrong arguments"
        // si Ok mise a jour de g_data.exit_value puis destroy tout
    }
}
*/
#include <stdio.h>

int main(int argc, char **argv)
{
    int exit_value;
//    t_cmd cmd
    unsigned char code;
    int code2;
    char *code_str;
    exit_value = 32;
    code = (unsigned char)exit_value;
    code2 = (int)code;
    printf("exit : %d, code %d\n", exit_value, code2);
    exit_value = 125;
 //   code_str = (char*)exit_value;
    printf("exit : %d, code %s\n", exit_value, code_str);
    return (0);
}