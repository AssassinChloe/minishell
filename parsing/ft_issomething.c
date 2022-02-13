/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issomething.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:26:32 by cassassi          #+#    #+#             */
/*   Updated: 2022/02/13 18:27:30 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r')
		return (1);
	return (0);
}

int	ft_ispipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == 39)
		return (1);
	else if (c == 34)
		return (2);
	return (0);
}

int	ft_isredir(char c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (2);
	return (0);
}

int	ft_special(char c)
{
	if (ft_isspace(c) == 0 && ft_isredir(c) == 0 && ft_ispipe(c) == 0)
		return (0);
	else
		return (1);
}
