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

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
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

void    ft_printtype(t_list *elem)
{
    t_list  *tmp;
    t_typage *type;

    tmp = elem;
    while (tmp)
    {
        type = (t_typage *)tmp->content;
        printf("type %d : %s\n", type->type, type->token);
        tmp = tmp->next;
    }
}

int ft_lexing(t_list *list)
{
    t_list *typelist;
    t_typage *tmp;
    t_list  *tmplist;

    typelist = NULL;
    tmplist = list;
    while (tmplist)
    {
        tmp = malloc(sizeof(t_typage));
        tmp->token = ft_strdup((char *)tmplist->content);
        tmp->type = get_token_type((char*)tmplist->content);
            if (typelist == NULL)
                typelist = ft_lstnew(tmp);
            else
                ft_lstadd_back(&typelist, ft_lstnew(tmp));
        tmplist = tmplist->next;
    }
    ft_printtype(typelist);
    return (0);

}
