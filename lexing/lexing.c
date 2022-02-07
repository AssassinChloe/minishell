/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:51:02 by vmercier          #+#    #+#             */
/*   Updated: 2022/01/31 16:13:18 by cassassi         ###   ########.fr       */
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

int ft_is_command(char *str)
{
    int fd;
    char *line;
    int ret;
    int isvalid;

    line = NULL;
    isvalid = 0;
    fd = open("lexing/commandes.txt", O_RDONLY);
    if (fd < 0)
        printf("erreur open\n");
    ret = get_next_line(fd, &line);
    while (ret > 0)
    {
        if (ft_strcmp(str, line) == 0)
            isvalid = 1;
        free(line);
        line = NULL;
        ret = get_next_line(fd, &line);
    }
    if (ret < 0)
        printf("erreur gnl \n");
    free(line);
    line = NULL;
    close(fd);
    return (isvalid);
}

int get_token_type(char *str, int *multicmd)
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
    else if (*multicmd == 0 && (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0
        || ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0
        || ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0
        || ft_strcmp(str,"exit") == 0))
    {
        tok = T_BUILTIN;
        *multicmd = 1;
    }
    else if (*multicmd == 0 && ft_is_command(str) == 1)
    {
       tok = T_CMD;
        *multicmd = 1;
    }
    else
        tok = T_STRING;
    return (tok);
}

void    ft_printtype(t_list *elem)
{
    t_list  *tmp;
    t_cmd   *type;
    int     i;

    i = 0;
    tmp = elem;
    while (tmp)
    {
        type = (t_cmd *)tmp->content;
        printf(" il y a %d argument dans la ligne de commande : \n", type->argc);
        while (i < type->argc)
        {
            printf("type %d : %s\n", type->type[i], type->argv[i]);
            i++;
        }
        i = 0;
        tmp = tmp->next;
    }
}

int ft_lexing(t_list **list)
{
    t_list  *commandlist;

    commandlist = NULL;
    ft_divide_pipe(*list, *list, &commandlist);
    ft_pipe(commandlist);
    ft_free_commandlist(&commandlist);
    return (0);
}