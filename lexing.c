/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:51:02 by vmercier          #+#    #+#             */
/*   Updated: 2022/01/21 09:51:18 by vmercier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define T_ERR 1
#define T_PIPE 2
#define T_CMD 3
#define T_FLAG 4
#define T_LOWER 5
#define T_GREATER 6
#define T_LLOWER 7
#define T_GGREATER 8
#define T_STRING 9
*/
#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int get_token_type(char *str)
{
    int tok;

    if (ft_strcmp(str, "|") == 0)
        tok = T_PIPE;
    else if (ft_strcmp(str, ";") == 0 || ft_strcmp(str, "||") == 0
        || ft_strcmp(str, "&&") == 0)
        tok = T_ERR;
    else if (ft_strcmp(str, "-n") == 0)
        tok = T_FLAG;
    else if (ft_strcmp(str, "<") == 0)
        tok = T_LOWER;
    else if (ft_strcmp(str, "<<") == 0)
        tok = T_LLOWER;
    else if (ft_strcmp(str, ">") == 0)
        tok = T_GREATER;
    else if (ft_strcmp(str, ">>") == 0)
        tok = T_GGREATER;
    else if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0
        || ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0
        || ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0
        || ft_strcmp(str,"exit") == 0 )
        tok = T_CMD;
    else
        tok = T_STRING;
    return (tok);
}
/*
int main(void)
{
    char *str1=";";
    char *str2="|";
    char *str3="echo";
    char *str4=">>";
    char *str5="truc";
    printf("token de %s : %d\n", str1, get_token_type(str1));
    printf("token de %s : %d\n", str2, get_token_type(str2));
    printf("token de %s : %d\n", str3, get_token_type(str3));
    printf("token de %s : %d\n", str4, get_token_type(str4));
    printf("token de %s : %d\n", str5, get_token_type(str5));
    return (0);
}
*/