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

char	*ft_handleis(char *str, int *i, int *multiple)
{
	if (ft_isspace(str[*i]) == 1)
	{
		while (str[*i] && ft_isspace(str[*i]) == 1)
			*i = *i + 1;
	}
	else if (ft_ispipe(str[*i]) == 1)
	{
		if (*multiple == 0)
			return (ft_extract_pipe(str, i, multiple));
		else
			return (is_forbidden_redir(i, multiple));
	}
	else if (ft_isredir(str[*i]) > 0)
	{
		if (*multiple == 0)
			return (extract_redir(str, i, multiple));
		else
			return (is_forbidden_redir(i, multiple));
	}
	return (NULL);
}

int	ft_parsetxt(char *str, int *i, char **tmp, int *multiple)
{
	while (str[*i] && ft_special(str[*i]) == 0)
	{
		*multiple = 0;
		while (str[*i] && ft_isquote(str[*i]) == 0 && ft_special(str[*i]) == 0)
		{	
			/*if (is_forbidden_char(str[*i]) == 1)
				return (-1);*/
			*tmp = ft_strjoin_char(*tmp, str[*i]);
			*i = *i + 1;
		}
		printf("%s\n", *tmp);
		if (has_dollar(*tmp) == 1)
			*tmp = ft_extract_var(*tmp);
		if (*tmp && strcmp(*tmp, "$") == 0 && (str[*i] && ft_isquote(str[*i]) > 0))
		{
			if (!((*i - 3) > 0 && ft_isquote(str[*i - 3]) > 0
				&& ft_isquote(str[*i - 3]) == ft_isquote(str[*i - 1])))
			{
				free (*tmp);
				*tmp = NULL;
			}
		}
		if (str[*i] && ft_isquote(str[*i]) > 0)
		{
			ft_concatquote(str, tmp, i);
			if (*i < 0)
				return (-1);
		}
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

int	ft_parsespecial(char *str, int *i, char	**tmp, t_list **tokens, int *multiple)
{
	int	hasquote;

	hasquote = 0;
	if (*tmp == NULL && *i < 0)
		return (-1);
	else if (*i >= 0 && (ft_strcmp(*tmp, "<<") == 0))
	{
		ft_addone(tokens, tmp);
		while (str[*i] && ft_isspace(str[*i]) == 1)
			*i = *i + 1;
		*tmp = ft_extract_limit(str, i, &hasquote);
		if (*tmp == NULL)
			return (0);
		if (*tmp == NULL && *i < 0)
			return (-1);
		if (hasquote == 1)
			*tmp = ft_addquote(*tmp);
		ft_addone(tokens, tmp);
		*multiple = 0;
	}
	else
		ft_addone(tokens, tmp);
	return (0);
}

void	ft_parse(char *str)
{
	int		i;
	char	*tmp;
	t_list	*tokens;
	int		multiple;

	i = 0;
	tmp = NULL;
	tokens = NULL;
	multiple = 1;
	while (str[i])
	{
		if (ft_parsetxt(str, &i, &tmp, &multiple) < 0)
			return (ft_freeparsing(&tmp, &tokens));
		ft_addone(&tokens, &tmp);
		while (str[i] && ft_special(str[i]) == 1)
		{
			tmp = ft_handleis(str, &i, &multiple);
			if (ft_parsespecial(str, &i, &tmp, &tokens, &multiple) < 0)
				return (ft_freeparsing(&tmp, &tokens));
		}
	}
	if (multiple == 1)
	{
		is_forbidden_redir(&i, &multiple);
		return (ft_freeparsing(&tmp, &tokens));
	}
	if (tokens == NULL)
		return ;
	ft_printchain(tokens);
	i = ft_lexing(&tokens);
	ft_lstclear(&tokens);
	if (i == 0)
	{
		free_g_data();
		exit(EXIT_SUCCESS);
	}
}
