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

int	ft_parsetxt(char *str, t_parse *parse)
{
	int	start;
	int	quote;

	start = 0;
	quote = 0;
	while (str[parse->i] && ft_special(str[parse->i]) == 0)
	{
		parse->multiple = 0;
		parse->pipe = 0;
		while (str[parse->i] && ft_isquote(str[parse->i]) == 0 && ft_special(str[parse->i]) == 0)
		{	
			parse->tmp = ft_strjoin_char(parse->tmp, str[parse->i]);
			parse->i++;
		}
		if (parse->tmp && has_dollar(parse->tmp + start) == 1)
		{
			if (str[parse->i - 1] && str[parse->i - 1] == '$' && ft_isquote(str[parse->i]) > 0)
				parse->tmp = ft_remove_dollar(parse->tmp, start);
			else
				parse->tmp = ft_extract_var(parse->tmp, quote, start);
		}
		if (str[parse->i] && ft_isquote(str[parse->i]) > 0)
		{
			quote++;
			ft_concatquote(str, &parse->tmp, &parse->i);
			if (parse->i < 0)
				return (-1);
		}
		start = ft_strlen(parse->tmp);
	}
	return (0);
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
		}
		else
		{
			tmp = ft_strjoin_char(tmp, str[*i]);
			*i = *i + 1;
		}
	}
	return (tmp);
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
		if (parse->tmp == NULL)
			return (0);
		if (parse->tmp == NULL && parse->i < 0)
			return (-1);
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

void	ft_parse(char *str)
{
	t_parse *parse;

	parse = malloc(sizeof(t_parse));
	parse->i = 0;
	parse->tmp = NULL;
	parse->tokens = NULL;
	parse->multiple = 0;
	parse->pipe = 1;
	parse->ret = 0;
	while (str[parse->i])
	{
		parse->ret = ft_parsetxt(str, parse);
		if (parse->ret < 0)
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
	if (parse->multiple == 1 || parse->pipe == 2)
	{
		is_forbidden_redir(parse);
		return (ft_freeparsing(&parse));
	}
	if (parse->tokens == NULL)
	{
		ft_freeparsing(&parse);
		return ;
	}
	parse->i = ft_lexing(&parse->tokens);
	if (parse->i == 0)
	{
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		close(STDERR_FILENO);
		ft_freeparsing(&parse);
		ft_free_splitlist(&g_data.split);
		g_data.split = NULL;
		free_g_data();
		exit(EXIT_SUCCESS);
	}
	ft_freeparsing(&parse);
}
