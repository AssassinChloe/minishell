#include "minishell.c"

t_env	*search_env(char *str, t_env *env) // je met env en parame au cas ou besoin env_export
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, str))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char    *get_env_value(vhar *str, t_env *env)
{
    char *env_value;
    t_env *tmp;

    tmp = search_env(str, env);
    if (!tmp)
        return (NULL);
    env_value = tmp->value;
    
    return (env_value);
}

int *change_value(char *key_str, char *value_str, t_env *env)
{
    t_env *tmp;

    tmp = search_env(key_str, env);
 //   if (!tmp)
        // a voir : add_var_env(key_str, value_str, env) ?
    
}