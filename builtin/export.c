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
affichage des variables (voir diff avec env  : 
export au début de chaque ligne + “” autour de la value 
+ ordre alphabetique de key : voir avec strcmp pour ordre d'impression)

- si 1 argument (ne contient pas de '=')
export NOMVARIABLE → la variable sera exportee dans tous les childs process 
(exemple : possibilite de faire echo $NOMVARIABLE apres 
avoir lance export NOMVARIABLE puis bash)
si elle n'existe pas il la cree sans valeur
n'affiche rien OK

- si 1 argument (contient un egal) 
creation d’une nouvelle variable (ex : export HOLA=bonjour) 
ou changement de la VALUE si la variable existait deja
n'affiche rien OK

- si plusieurs arguments, traire successivemet chaque arguments selon 
les regles ci-dessus en fonction de la presence de = ou pas ->OK

-identifiant valide : lettres ou chifres ou _, pas autre chose 
memes regles d'extension des $x que pour le parsing sauf qu'il ne doit 
pas rester de $ dans le nom
(ex : $x entre ' ' -> nom invalide, $x entre "" -> OK)

- memes regles d'extension des $ que pour le parsing, sauf ' + $ -> \$... 

- doit-on gerer export truc+=chose ? OK

RESTE A FAIRE : 
	couper fonction principale 
	impression par ordre alpha

*/

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
	char	**spvar;

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
				spvar = ft_split_env_plus(cmd.av[i]);
			else if (has_equal(cmd.av[i]))
				spvar = ft_split_env(cmd.av[i]);
			if (!format_key_ok(spvar[0]))
			{
				ft_putstr_fd("export: `", 2);
				ft_putstr_fd(spvar[0], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				free_tab2(spvar);
				g_data.exit_value = 1;
				return (1);
			}
			if (!already_in_env(spvar[0]))
				add_env_value(spvar[0], spvar[1], 1);
			else
			{
				if (has_plus_equal(cmd.av[i]))
					spvar[1] = ft_strjoin(get_env_value(spvar[0]), spvar[1]);
				search_var(spvar[0])->value = ft_strdup(spvar[1]);
			}
			free_tab2(spvar);
		}
	}
	return (0);
}
