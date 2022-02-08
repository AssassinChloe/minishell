#include "minishell.h"

/*
si arg = nom d'une variable -> suppression de cette variable
g_data.exit_value = 0

si arg = nom nom valide (ex : contient - ) : message error : not a valid identifier
g_data.exit_value = 1

si pas d'arg -> ne fait rien
g_data.exit_value = 0

si plusieurs arguments : 
traite tous les arguments les uns a la suite des autres, s'arrte si erreur
*/


int ft_unset(t_cmd cmd)
{
    printf(" pour utilisation param et compil %d", cmd.argc);
    return (0);
}