#include "minishell.h"



t_env   *search_var(char *str)// renvoi un pointeur sur la var de key STR (voir si env en paam)
{
    t_env   *var;

    var = g_data.env;
    while (var)
	{
        if (!ft_strcmp(var->key, str))
		{
			printf("key : %s, value : %s\n", var->key, var->value); // uniquement pour test
			return (var);
		}
		var = var->next;
	}

    return (NULL);
}

char    *get_env_value(char *str) // renvoi la str VALUE de la var STR (voir si env en var)
{
    char *env_value;
    t_env *tmp;

    tmp = search_var(str);
    if (!tmp)
        return (NULL);
    env_value = tmp->value;
	printf("value de %s : %s", str, env_value); // uniquement pour test
    
    return (env_value);
}


int ft_cd(t_cmd cmd)
{
    char *src_path;
    char *dest_path;

    if (cmd.argc == 1)
        // objectif : faire retour a home
        // voir si variable HOME bien dnas les var env, sinon erreur
        // recuperation de home
        {
            dest_path = get_env_value("HOME");
            printf("dest_path = %s\n", dest_path); //pour test
        }
    if (cmd.argc > 2)
        {
        ft_putstr_fd("too many arguments", STDOUT_FILENO);// reeor two many arguments
        g_data.exit_value = 1;
        }
    else
    {
        src_path = getcwd(NULL, 0);
        if (chdir(cmd.argv[1])) // si chemin non valide -> error
        {
            free(src_path);
            ft_putstr_fd("No such file or directory", STDOUT_FILENO);//error No such file or directory + 
            g_data.exit_value = 1;
            return(1);
        }
        dest_path = getcwd(NULL, 0);
        printf("dest_path = %s\n", dest_path);
        printf("src_path = %s\n", src_path);
 //   modification des var OLDPWD (avec src_path)
 //   modification des var PWD (avec dest_var)
        free(src_path);
        free(dest_path);
    }
    return (0);
}
/*
int	main(int ac, char **av, char **envp)
{
    t_cmd cmd;
    cmd.argc = ac;
    cmd.argv = av;

    init_data(envp);
    ft_cd(cmd);
    ft_pwd();

	return (0);
}
*/