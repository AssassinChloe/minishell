/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:12:29 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/13 19:03:39 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_addquote(char *str)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin_char(tmp, '"');
	tmp = ft_strjoin(tmp, str);
	tmp = ft_strjoin_char(tmp, '"');
	return (tmp);
}

int	ft_isclosed(char *str, int i)
{
	char	c;

	c = str[i];
	i++;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_copyquote(int *i, char *str, int ret)
{
	int		j;
	char	*quote;

	j = 0;
	quote = malloc(sizeof(char) * (ret - *i) + 2);
	while (*i <= ret)
	{
		quote[j] = str[*i];
		j++;
		*i = *i + 1;
	}
	quote[j] = '\0';
	return (quote);
}

char	*ft_handle_quote(char *str, int *i, int keepquote)
{
	int		ret;
	char	*quote;

	quote = NULL;
	ret = ft_isclosed(str, *i);
	if (ret < 0)
	{
		*i = -1;
		printf("minishell: error the quote is not closed\n");
		return (NULL);
	}
	else
	{
		if (keepquote == 0)
		{
			*i = *i + 1;
			ret--;
		}
		quote = ft_copyquote(i, str, ret);
		if (keepquote == 0)
			*i = *i + 1;
	}
	return (quote);
}

void	ft_concatquote(char *str, char **tmp, int *i)
{
	int		ret;
	char	*tmp2;

	tmp2 = NULL;
	ret = ft_isquote(str[*i]);
	tmp2 = ft_handle_quote(str, i, 0);
	if (tmp2 == NULL && *i < 0)
		return ;
	if (ret == 2 && has_dollar(tmp2) == 1)
		tmp2 = ft_extract_var(tmp2, 1);
	if (*tmp != NULL)
		*tmp = ft_strjoin(*tmp, tmp2);
	else
		*tmp = ft_strdup(tmp2);
	free(tmp2);
}
