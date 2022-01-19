#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"



void    ft_parse(char *str);
int ft_isspace(char c);
int ft_isquote(char c);
int ft_issimplequote(char c);
int ft_isdoublequote(char c);
int ft_ispipe(char c);


#endif