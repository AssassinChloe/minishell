NAME	=	minishell

SRCS	=	minishell.c parsing.c ft_issomething.c handlechainlist.c has_dollar.c handle_quote.c handle_redir.c\
			

OBJSD   =	.obj/

OBJS    =	$(addprefix $(OBJSD), $(SRCS:%.c=%.o))

INC		=	-I minishell.h

LIB		=	libft/libft.a

FLAG	=	-Wall -Wextra -Werror -lreadline

CC		=	clang

all		:	$(NAME)

$(NAME)	:	$(OBJS)
				$(MAKE) -C libft
				$(CC) -o $(NAME) $(OBJS) $(LIB) $(FLAG)

clean	:	
				$(MAKE) clean -C libft
				rm -rf $(OBJSD)

fclean	:	clean
				$(MAKE) fclean -C libft
				rm -rf $(NAME)

re		:	fclean all

$(OBJSD)%.o:%.c
			@mkdir -p $(OBJSD)
			$(CC) $(INC) -o $@ -c $<
