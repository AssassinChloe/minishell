/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 10:30:34 by vmercier          #+#    #+#             */
/*   Updated: 2022/02/01 10:31:45 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_env(char **args, t_env *var_list)
{
	t_env	*var;

	if (var_list)
	{
		(void)args;
		var = var_list;
		while (var)
		{
			ft_putstr_fd(var->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(var->value, STDOUT_FILENO);
			var = var->next;
		}
	}
	return (0);
}
