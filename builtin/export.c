/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:45:41 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/16 13:45:45 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
- si pas d'argument (argc == 1)
affichage des variables (voir diff avec env  : export au début de chaque ligne + 
“” autour de la value + ordre alphabetique de key : voir avec strcmp pour ordre d'impression)

- si 1 argument (ne contient pas de '=')
export NOMVARIABLE → la variable sera exportee dans tous les childs process 
(exemple : possibilite de faire echo $NOMVARIABLE apres 
avoir lance export NOMVARIABLE puis bash)
si elle n'existe pas il la cree sans valeur
n'affiche rien

- si 1 argument (contient un egal) 
creation d’une nouvelle variable (ex : export HOLA=bonjour) 
ou changement de la VALUE si la variable existait deja
n'affiche rien

- si plusieurs arguments, traire successivemet chaque arguments selon les regles ci-dessus 
en fonction de la presence de = ou pas ->OK

-identifiant valide : lettres ou chifres ou _, pas autre chose 
memes regles d'extension des $x que pour le parsing sauf qu'il ne doit pas rester de $ dans le nom
(ex : $x entre ' ' -> nom invalide, $x entre "" -> OK)

- memes regles d'extension des $ que pour le parsing, sauf ' + $ -> \$... 

- doit-on gerer export truc+=chose ? 
qui vient ajouter chose a la valeur deja d2finie avant
*/
/*
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
*/
/*
t_env *modify_env_value(t_env *var, char *new_value)
{
	var->value = ft_strdup(new_value);
	return(var);
}
*/

t_env	*find_last_env(void)
{
	t_env	*env;

	env = g_data.env;
	if (!env)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

int	already_in_env(char *arg)
{
	t_env	*tmp;

	tmp = g_data.env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, arg))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	format_key_ok(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && !(str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	has_equal(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	has_plus_equal(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i + 1])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	add_env_value(char *newkey, char *newvalue, int int_value)
{
	t_env	*last;
	t_env	*new;

	last = g_data.env;
	new = malloc(sizeof(char *) * 3);
	new->key = ft_strdup(newkey);
	new->value = ft_strdup(newvalue);
	new->has_value = int_value;
	new->next = NULL;
//	printf("New value : key = %s, value = %s, has_value = %d\n", new->key, new->value, new->has_value); //
	last = find_last_env();
	last->next = new;
//	printf("Last value : key = %s, value = %s, next key = %s\n", last->key, last->value, last->next->key); //
}

int	print_exp_list(void)
{
	t_env	*var;

	var = g_data.env;
	while (var)
	{
		ft_putstr_fd("Export ", STDOUT_FILENO);
		ft_putstr_fd(var->key, STDOUT_FILENO);
		if (var->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(var->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		var = var->next;
	}
	return (0);
}



int	ft_export(t_cmd cmd)
{
	int		i;
	char **split_var;

	if (cmd.argc == 1)
	{
		print_exp_list();
		return (0);
	}
	i = 0;
	while (cmd.av[++i])
	{
		if (!has_equal(cmd.av[i]))
		{
			if (format_key_ok(cmd.av[i]))
				add_env_value(cmd.av[i], NULL, 0);
			else
			{
				ft_putstr_fd("export: `", 2);
				ft_putstr_fd(cmd.av[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				g_data.exit_value = 1;
				return (1);
			}
		}
		else
		{
			if (has_plus_equal(cmd.av[i]))
			{
				split_var = ft_split_env_plus(cmd.av[i]);
	//			printf("split_var_plus_equal = %s / %s\n", split_var[0], split_var[1]);
			}
			else if (has_equal(cmd.av[i]))
			{
				split_var = ft_split_env(cmd.av[i]);
	//			printf("split_var_equal = %s / %s\n", split_var[0], split_var[1]);
			}
	//		printf("format key OK ? %d\n", format_key_ok(split_var[0]));
			if (!format_key_ok(split_var[0]))
			{
				ft_putstr_fd("export: `", 2);
				ft_putstr_fd(split_var[0], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				free_tab2(split_var);
				g_data.exit_value = 1;
				return (1);
			}
		//	printf("already in env ? %d\n", already_in_env(split_var[0]));
			if (!already_in_env(split_var[0]))
				add_env_value(split_var[0], split_var[1], 1);// add new env avec splitvar 0 et 1
			else
			{
				if (has_plus_equal(cmd.av[i]))
					split_var[1]=ft_strjoin(get_env_value(split_var[0]), split_var[1]);
		//		change_env_value(split_var[0], split_var[1], 1);// add new env avec splitvar 0 et 1
				search_var(split_var[0])->value = ft_strdup(split_var[1]);
			}
		}
	}
	return (0);
}