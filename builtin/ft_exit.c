

#include "minishell.h" //a modifier opur test : ../header/minishell.h

//t_data g_data; // pour test a supprimer

// reste a faire : fonction destroy_all 
//+ voir si on a besoin de renvoyer la meme valeur que g_data.exit_value

int check_format_exit(char *str)
{
    int i;

    i = 0;
    while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            i++;
        else
            return (0);
    }
    return (1);
}

int ft_exit(t_cmd cmd)
{
    int number;
    int valid;

    if (cmd.argc == 1)
    {
        ft_putstr_fd("exit\n", STDERR_FILENO);
        g_data.exit_value = 0;
//      destroy_all(); // fonction a faire
    }
    if (cmd.argc > 2)
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
        g_data.exit_value = 1;
        return (1);
    }
    if (cmd.argc == 2)
    {
        valid = check_format_exit(cmd.argv[1]);
        if (!valid)
        {
            ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
            ft_putstr_fd(cmd.argv[1], STDERR_FILENO);
            ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
            g_data.exit_value = 2;
            return (2);
        }
        number = ft_atoi(cmd.argv[1]); 
        if (number  < 0)
        {
            while (number >= 0 && number <= 255)
            number = number + 256;
        } 
        if (number > 255)
            number = number % 256;
        printf ("number = %d\n", number);
        g_data.exit_value = number;
         // destroy_all(); fonction a faire
        return (number);
    }
    return (0);
}
/*
#include <stdio.h>

int main(int argc, char **argv)
{
    int exitvalue;
    t_cmd cmd;
    cmd.argc = argc;
    cmd.argv = argv;
    exitvalue = ft_exit(cmd);
    printf("exit_value = %d\n", exitvalue);

    return (0);
}
*/