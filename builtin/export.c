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
+ ordre alphabetique de key 

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

*/

int	err_format_id_export(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_data.exit_value = 1;
	return (1);
}

int	err_format_value_export(char **tab)
{
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
	g_data.exit_value = 2;
	free_tab2(tab);
	return (2);
}

int	ft_export_with_equal(char *str)
{
	char	**spvar;

	if (has_plus_equal(str))
		spvar = ft_split_env_plus(str);
	else
		spvar = ft_split_env(str);
	if (!format_key_ok(spvar[0]))
	{
		free_tab2(spvar);
		return (err_format_id_export(str));
	}
	if (!format_value_ok(spvar[1]))
		return (err_format_value_export(spvar));
	if (!already_in_env(spvar[0]))
		add_env_value(spvar[0], spvar[1], 1);
	else
	{
		if (has_plus_equal(str))
			spvar[1] = ft_strjoin_d(get_env_value(spvar[0]), spvar[1]);
		free(search_var(spvar[0])->value);
		search_var(spvar[0])->value = ft_strdup(spvar[1]);
		search_var(spvar[0])->has_value = 1;
	}
	free_tab2(spvar);
	return (0);
}

int	ft_export_invalid_option(char *str)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putchar_fd(str[0], 2);
	if (str[1])
		ft_putchar_fd(str[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
	g_data.exit_value = 2;
	return (2);
}

int	ft_export(t_cmd cmd)
{
	int		i;
	int		ret;
	char	**table;

	if (cmd.argc == 1)
	{
		table = sort_table(table_export_key());
		return (print_table_export(table));
	}
	i = 0;
	ret = 0;
	while (cmd.av[++i])
	{
		if (cmd.av[1][0] == '-' && cmd.av[1][1])
			return (ft_export_invalid_option(cmd.av[1]));
		if (!has_equal(cmd.av[i]))
		{
			if (format_key_ok(cmd.av[i]) && !already_in_env(cmd.av[i]))
				add_env_value(cmd.av[i], NULL, 0);
			else if (!format_key_ok(cmd.av[i]))
				ret = err_format_id_export(cmd.av[i]);
		}
		else
			ret = ft_export_with_equal(cmd.av[i]);
	}
	return (ret);
}
