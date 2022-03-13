/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:43:36 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/13 19:01:50 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parsetxt(char *str, t_parse *parse)
{
	while (str[parse->i] && ft_special(str[parse->i]) == 0)
	{
		parse->multiple = 0;
		parse->pipe = 0;
		while (str[parse->i] && ft_isquote(str[parse->i]) == 0
			&& ft_special(str[parse->i]) == 0)
		{	
			parse->tmp = ft_strjoin_char(parse->tmp, str[parse->i]);
			parse->i++;
		}
		if (parse->tmp && has_dollar(parse->tmp + parse->buf) == 1)
			ft_deal_with_dollar(str, parse);
		if (str[parse->i] && ft_isquote(str[parse->i]) > 0)
		{
			parse->quote++;
			ft_concatquote(str, &parse->tmp, &parse->i);
			if (parse->i < 0)
				return ;
		}
		parse->buf = ft_strlen(parse->tmp);
	}
	parse->buf = 0;
	parse->quote = 0;
}

int	ft_parsespecial(char *str, t_parse *parse)
{
	int	hasquote;

	hasquote = 0;
	if (parse->tmp == NULL && parse->i < 0)
		return (-1);
	else if (parse->tmp && parse->i >= 0 && (ft_strcmp(parse->tmp, "<<") == 0))
	{
		ft_addone(&parse->tokens, &parse->tmp);
		while (str[parse->i] && ft_isspace(str[parse->i]) == 1)
			parse->i++;
		parse->tmp = ft_extract_limit(str, &parse->i, &hasquote);
		if (parse->tmp == NULL && parse->i < 0)
			return (-1);
		if (parse->tmp == NULL)
			return (0);
		if (hasquote == 1)
			parse->tmp = ft_addquote(parse->tmp);
		ft_addone(&parse->tokens, &parse->tmp);
		parse->pipe = 0;
		parse->multiple = 0;
	}
	else
		ft_addone(&parse->tokens, &parse->tmp);
	return (0);
}

t_parse	*ft_init_parse(void)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	parse->i = 0;
	parse->tmp = NULL;
	parse->tokens = NULL;
	parse->multiple = 0;
	parse->pipe = 1;
	parse->quote = 0;
	parse->buf = 0;
	return (parse);
}

void	ft_parse(char *str)
{
	t_parse	*parse;

	parse = ft_init_parse();
	while (str[parse->i])
	{
		ft_parsetxt(str, parse);
		if (parse->i < 0)
			return (ft_freeparsing(&parse));
		else
			ft_addone(&parse->tokens, &parse->tmp);
		while (str[parse->i] && ft_special(str[parse->i]) == 1)
		{
			parse->tmp = ft_handleis(str, parse);
			if (ft_parsespecial(str, parse) < 0)
				return (ft_freeparsing(&parse));
		}
	}
	if (parse->tokens == NULL || parse->multiple == 1 || parse->pipe == 2)
	{
		if (parse->tokens != NULL)
			is_forbidden_redir(parse);
		return (ft_freeparsing(&parse));
	}
	ft_lexing(parse);
}
