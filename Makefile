NAME	= minishell

SRCS	= parsing.c

OBJSD   = .obj/

OBJS    = $(addprefix $(OBJSD), $(SRCS:%.c=%.o))

INC		= -I minishell.h

FLAG	= -Wall -Wextra -Werror -lreadline

CC		= clang

all		:	$(NAME)

$(NAME)	:	$(OBJS)
				$(CC) -o $(NAME) $(OBJS) $(FLAG)

clean	:	
				rm -rf $(OBJSD)

fclean	:	clean
				rm -rf $(NAME)

re		:	fclean all

$(OBJSD)%.o:%.c
			@mkdir -p $(OBJSD)
			$(CC) $(INC) -o $@ -c $<
