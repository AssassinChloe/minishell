# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cassassi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 14:05:42 by cassassi          #+#    #+#              #
#    Updated: 2022/01/31 14:06:58 by cassassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	=	minishell.c split_env.c\
			$(addprefix $(PARSDIR), $(PARSING))\
			$(addprefix $(LEXDIR), $(LEXING))\
			$(addprefix $(BUILDIR), $(BUILTIN))\
			$(addprefix $(EXECDIR), $(EXEC))\

PARSING	=	parsing.c ft_issomething.c handlechainlist.c has_dollar.c handle_quote.c handle_redir.c\
			cleanparsing.c

PARSDIR	=	parsing/

LEXING	=	lexing.c build_command_list.c get_path.c redirection.c redirection_2.c modif_command_list.c

LEXDIR	=	lexing/

EXEC	=	execution.c pipe.c closing_pipe.c 

EXECDIR	=	execution/

BUILTIN	=	echo.c pwd.c env.c launch_builtin.c export.c ft_cd.c ft_exit.c unset.c 

BUILDIR	=	builtin/

OBJSD   =	.obj/

OBJS    =	$(addprefix $(OBJSD), $(SRCS:%.c=%.o))

INC		=	-I header/

LIB		=	libft/libft.a

FLAG	=	-Wall -Wextra -Werror 

CC		=	clang

all		:	$(NAME)

$(NAME)	:	$(OBJS)
				$(MAKE) -C libft
				$(CC) -o $(NAME) $(FLAG) -lreadline $(OBJS) $(LIB) 

clean	:	
				$(MAKE) clean -C libft
				rm -rf $(OBJSD)

fclean	:	clean
				$(MAKE) fclean -C libft
				rm -rf $(NAME)

re		:	fclean all

$(OBJSD)%.o:%.c
			@mkdir -p $(OBJSD)
			@mkdir -p $(OBJSD)$(PARSDIR)
			@mkdir -p $(OBJSD)$(LEXDIR)
			@mkdir -p $(OBJSD)$(BUILDIR)
			@mkdir -p $(OBJSD)$(EXECDIR)
			$(CC) $(INC) $(FLAG) -o $@ -c $<
