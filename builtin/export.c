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

int	count_var_env(void)
{
	int		nb_var;
	t_env	*var;

	var = g_data.env;
	nb_var = 0;
	while (var->next)
	{
		nb_var++;
		var = var->next;
	}
	return (nb_var);
}

char	**table_export_key(void)
{
	char	**table;
	int		nb_var;
	t_env	*var;

	var = g_data.env;
	nb_var = count_var_env();
	table = (char **)malloc(sizeof(char *) * (nb_var + 2));
	if (!table)
		return (NULL);
	var = g_data.env;
	table[nb_var + 1] = NULL;
	while (var->next)
	{
		table[nb_var] = ft_strdup(var->key);
		nb_var--;
		var = var->next;
	}
	table[nb_var] = ft_strdup(var->key);
	return (table);
}

char	**sort_table(char **table)
{
	int		i;
	int		j;
	char	*tmp;

	if (*table == NULL)
		return (NULL);
	i = 0;
	while (table[i])
	{
		j = i;
		while (j && ft_strcmp(table[j], table[j - 1]) < 0)
		{
			tmp = table[j];
			table[j] = table[j - 1];
			table[j - 1] = tmp;
			j--;
		}
		i++;
	}
	return (table);
}

void	free_table_string(char **table)
{
	int	i;

	i = 0;
	if (table)
	{
		while (table[i])
		{
			free(table[i]);
			i++;
		}
		free(table);
	}
}

int	print_table_export(char **table)
{
	int		i;
	t_env	*var;
	char	*var_value;

	i = 0;
	while (table[i])
	{
		ft_putstr_fd("Export ", STDOUT_FILENO);
		ft_putstr_fd(table[i], STDOUT_FILENO);
		var = search_var(table[i]);
		if (var->value)
		{
			var_value = (get_env_value(table[i]));
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(var_value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			free(var_value);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	free_table_string(table);
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

char	*ft_strjoin_d(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*s3;

	i = 0;
	j = 0;
	if (!(s1) && !(s2))
		return (NULL);
	else if (!s1)
		return (s2);
	else if (!s2)
		return (s1);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + (ft_strlen(s2)) + 1));
	if (!(s3))
		return (NULL);
	while (s1[i])
		s3[j++] = s1[i++];
	i = 0;
	free(s1);
	while (s2[i])
		s3[j++] = s2[i++];
	s3[j] = '\0';
	free(s2);
	return (s3);
}

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
		err_format_id_export(str);
		free_tab2(spvar);
		return (1);
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
		table = table_export_key();
		table = sort_table(table);
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
