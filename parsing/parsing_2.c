/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:18:59 by cassassi          #+#    #+#             */
/*   Updated: 2022/03/12 15:19:03 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_handleis(char *str, t_parse *parse)
{
	if (ft_isspace(str[parse->i]) == 1)
	{
		while (str[parse->i] && ft_isspace(str[parse->i]) == 1)
			parse->i++;
	}
	else if (ft_ispipe(str[parse->i]) == 1)
	{
		if (parse->pipe == 0 && parse->multiple == 0)
			return (ft_extract_pipe(str, parse));
		else
			return (is_forbidden_redir(parse));
	}
	else if (ft_isredir(str[parse->i]) > 0)
	{
		if (parse->multiple == 0)
			return (extract_redir(str, parse));
		else
			return (is_forbidden_redir(parse));
	}
	return (NULL);
}

void	ft_deal_with_dollar(char *str, t_parse *parse)
{
	if (str[parse->i - 1] && str[parse->i - 1] == '$'
		&& ft_isquote(str[parse->i]) > 0)
		parse->tmp = ft_remove_dollar(parse->tmp, parse->buf);
	else
		parse->tmp = ft_extract(parse->tmp, parse->quote, parse->buf);
}

char	*ft_extract_limit(char *str, int *i, int *hasquote)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	while (str[*i] && ft_special(str[*i]) == 0)
	{
		if (ft_isquote(str[*i]) > 0)
		{
			*hasquote = 1;
			tmp2 = ft_handle_quote(str, i, 0);
			if (*i < 0)
				return (NULL);
			tmp = ft_strjoin(tmp, tmp2);
			free(tmp2);
			tmp2 = NULL;
		}
		else
		{
			tmp = ft_strjoin_char(tmp, str[*i]);
			*i = *i + 1;
		}
	}
	return (tmp);
}
