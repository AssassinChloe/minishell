/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:13:44 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/13 18:26:07 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdoubleredir(char *str, int i)
{
	int	ret;

	ret = ft_isredir(str[i]);
	if (str[i + 1])
	{
		if (ft_isredir(str[i + 1]) == 0)
			return (0);
		else
		{
			if (ft_isredir(str[i + 1]) == ret)
				return (1);
			else
				return (-1);
		}
	}
	return (0);
}

char	*extract_doubleredir(char *str, int *i)
{
	char	*quote;
	int		j;

	j = 0;
	quote = malloc(sizeof(char) * 3);
	j = 0;
	while (j < 2)
	{
		quote[j] = str[*i];
		j++;
		*i = *i + 1;
	}
	quote[j] = '\0';
	return (quote);
}

char	*extract_redir(char *str, t_parse *parse)
{
	int		ret;
	char	*quote;

	parse->multiple = 1;
	ret = ft_isdoubleredir(str, parse->i);
	if (ret == 1)
		return (extract_doubleredir(str, &parse->i));
	else if (ret == 0)
	{
		quote = malloc(sizeof(char) * 2);
		quote[0] = str[parse->i];
		quote[1] = '\0';
		parse->i++;
		return (quote);
	}
	else
		return (is_forbidden_redir(parse));
}

char	*ft_extract_pipe(char *str, t_parse *parse)
{
	char	*quote;

	parse->multiple = 0;
	parse->pipe = 1;
	quote = malloc(sizeof(char) * 2);
	quote[0] = str[parse->i];
	quote[1] = '\0';
	parse->i++;
	return (quote);
}
