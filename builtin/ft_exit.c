/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:47:37 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/16 13:47:45 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" //a modifier opur test : ../header/minishell.h

//t_data g_data; // pour test a supprimer

// reste a faire : fonction destroy_all 
//+ voir si on a besoin de renvoyer la meme valeur que g_data.exit_value

int	check_format_exit(char *str)
{
	int	i;

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

void	free_env(void)
{
	t_env	*tmp;
	t_env	*env;

	env = g_data.env;
	tmp = env;
	while (tmp)
	{
		printf("tmp a nettoyer : %s\n", tmp->key);
		env = env->next;
		printf("env value : %s\n", env->key);
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = NULL;
		if (env->next)
			tmp = env;
		printf("tmp de fin de boucle : %s\n", tmp->key);
	}
	printf("boucle finie\n");
	free(g_data.env);
	g_data.env = NULL;
	printf("env freed\n");
}
/*
typedef struct s_data // globale ?
{
	char	*line;
	t_cmd	*cmd_lst;
	char	**splited_line;
	char	**args;
	t_env	*env;
	int		exit_value;
	int		nb_pipe;
	int		execution; // pour dire si on est en cours d'execution ou non
	int		loop; // variable pour maintien de la boucle while
}		t_data;
*/

void	free_g_data()
{
	printf("passe par free g_data\n");
	if (g_data.env)
		free_env();
	if (g_data.line)
		free(g_data.line);
}

int	ft_exit(t_cmd cmd)
{
	int	number;
	int	valid;

	if (cmd.argc == 1)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		g_data.exit_value = 0;
		free_g_data(); //destroy_all(); // fonction a faire
		g_data.loop = -1;
	}
	if (cmd.argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_data.exit_value = 1;
		return (1);
	}
	if (cmd.argc == 2)
	{
		valid = check_format_exit(cmd.av[1]);
		if (!valid)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd.av[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			g_data.exit_value = 2;
			return (2);
		}
		number = ft_atoi(cmd.av[1]); 
		if (number  < 0)
		{
			while (number >= 0 && number <= 255)
			number = number + 256;
		}
		if (number > 255)
			number = number % 256;
		printf ("number = %d\n", number); //pour test
		g_data.exit_value = number;
		g_data.loop = 0;
		free_g_data(); //
		print_exp_list(); //pour test
		g_data.loop = -1;
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
    cmd.av = argv;
    exitvalue = ft_exit(cmd);
    printf("exit_value = %d\n", exitvalue);

    return (0);
}
*/
