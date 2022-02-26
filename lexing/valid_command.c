#include "minishell.h"

int is_valid_cmd(t_cmd *cmd)
{
    struct stat	*test;
    int         ret;
    
    ret = 0;
    test = malloc(sizeof(struct stat));
	if (cmd->av[0] && stat(cmd->av[0], test) >= 0 && S_ISDIR(test->st_mode) == 1)
	{	
        free(test);
	    test = NULL;
		return (126);
	}
    free(test);
	test = NULL;
    if (ft_strcmp(cmd->av[0], "") == 0 || (cmd->type[0] != T_BUILTIN && ft_get_cmd_path(cmd) > 0))
		return (127);
	return (0);
}