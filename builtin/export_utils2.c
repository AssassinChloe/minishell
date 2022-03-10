/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:23:09 by vmercier          #+#    #+#             */
/*   Updated: 2022/03/10 12:23:12 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	table = NULL;
}

int	print_table_export(void)
{
	int		i;
	t_env	*var;
	char	*var_value;
	char	**table;

	i = 0;
	table = sort_table(table_export_key());
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
