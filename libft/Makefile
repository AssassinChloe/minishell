# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cassassi <cassassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/18 15:59:27 by cassassi          #+#    #+#              #
#    Updated: 2021/10/11 10:41:00 by cassassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	= ft_atoi.c ft_strncmp.c ft_strlen.c ft_memmove.c ft_memchr.c \
	  ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memcmp.c \
	  ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	  ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strlcpy.c \
	  ft_strlcat.c ft_strnstr.c ft_calloc.c ft_strdup.c ft_substr.c \
	  ft_strjoin.c ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_itoa.c\
	  ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_strjoin_char.c\
	  get_next_line.c get_next_line_utils.c ft_atoll.c ft_lstnew.c\
	  ft_lstadd_back.c ft_lstlast.c ft_lstdelone.c ft_lstclear.c

OBJS    = $(SRCS:%.c=%.o)

CC	= gcc

RM	= rm -rf

INC	= libft.h

FLAGS	= -Wall -Wextra -Werror

$(NAME):	$(OBJS)
			$(CC) -c $(FLAGS) $(INC) $(SRCS)
			ar -rc $(NAME) $(OBJS)

all :		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all