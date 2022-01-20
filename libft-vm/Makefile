# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmercier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/04 11:40:40 by vmercier          #+#    #+#              #
#    Updated: 2021/06/04 11:41:26 by vmercier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PART = 	./ft_recursive_power.c ./ft_calloc_exit.c ./ft_atoi.c ./ft_bzero.c ./ft_calloc.c ./ft_isalnum.c ./ft_isalpha.c ./ft_isascii.c ./ft_isdigit.c ./ft_isprint.c ./ft_itoa.c ./ft_memccpy.c ./ft_memchr.c ./ft_memcmp.c ./ft_memcpy.c ./ft_memmove.c ./ft_memset.c ./ft_putchar_fd.c ./ft_putendl_fd.c ./ft_putnbr_fd.c ./ft_putstr_fd.c ./ft_strchr.c ./ft_strdup.c ./ft_strjoin.c ./ft_strlcat.c ./ft_strlcpy.c ./ft_strlen.c ./ft_strmapi.c ./ft_strncmp.c ./ft_strnstr.c ./ft_strrchr.c ./ft_split.c ./ft_strtrim.c ./ft_substr.c ./ft_tolower.c ./ft_toupper.c

SRC_BONUS = ./ft_lstadd_back.c ./ft_lstadd_front.c ./ft_lstclear.c ./ft_lstdelone.c ./ft_lstiter.c ./ft_lstlast.c ./ft_lstmap.c ./ft_lstnew.c ./ft_lstsize.c
			
NAME = libft.a

FLAGS = -Wall -Wextra -Werror

CC = gcc

RM = rm -f

HDRS = libft.h

OBJ_PART = $(SRC_PART:.c=.o)

OBJ_BONUS = $(OBJ_PART) $(SRC_BONUS:.c=.o)

all: $(NAME)

.c.o:
	@$(CC) $(FLAGS) -I includes -c $< -o ${<:.c=.o}

$(NAME): $(OBJ_PART) $(HDRS)
	@ar rc $(NAME) $(OBJ_PART)
	@ranlib $(NAME)
	

bonus: $(OBJ_BONUS) $(HDRS)
	ar rc $(NAME) $(OBJ_BONUS)
	ranlib $(NAME)

clean:
	$(RM) $(OBJ_BONUS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
