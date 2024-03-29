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

SRCS	=	minishell.c printf_error.c signals.c\
			$(addprefix $(PARSDIR), $(PARSING))\
			$(addprefix $(LEXDIR), $(LEXING))\
			$(addprefix $(BUILDIR), $(BUILTIN))\
			$(addprefix $(EXECDIR), $(EXEC))\

PARSING	=	parsing.c ft_issomething.c handlechainlist.c has_dollar.c handle_quote.c handle_redir.c\
			cleanparsing.c split_list.c has_dollar_utils.c parsing_2.c

PARSDIR	=	parsing/

LEXING	=	lexing.c build_command_list.c valid_command.c get_path.c redirection.c redirection_utils.c\
			modif_command_list.c redirection_error.c handle_heredoc.c divide_around_pipe.c

LEXDIR	=	lexing/

EXEC	=	execution.c pipe.c execution_2.c

EXECDIR	=	execution/

BUILTIN	=	echo.c pwd.c env.c launch_builtin.c export.c ft_cd.c ft_exit.c unset.c unset_utils.c\
			env_utils.c env_init.c split_env.c exit_utils.c cd_utils.c export_utils.c export_utils2.c	

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
