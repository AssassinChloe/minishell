#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

# define T_ERR 1
# define T_PIPE 2
# define T_CMD 3
# define T_FLAG 4
# define T_LOWER 5
# define T_GREATER 6
# define T_LLOWER 7
# define T_GGREATER 8
# define T_STRING 9

void    ft_parse(char *str);
int ft_isspace(char c);
int ft_isquote(char c);
int ft_issimplequote(char c);
int ft_isdoublequote(char c);
int ft_ispipe(char c);
void    ft_printchain(t_list *elem);
void    ft_addone(t_list **tokens, char **tmp);
int	has_dollar(char *str);
int	ft_strcmp(char *s1, char *s2);
int get_token_type(char *str);
void	ft_extract_var(t_list **tokens, char *str);


#endif