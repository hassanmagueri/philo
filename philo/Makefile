# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 01:46:42 by emagueri          #+#    #+#              #
#    Updated: 2024/03/24 17:05:06 by emagueri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	ft_atoi.c \
		init.c \
		main.c \
		monitor.c \
		philo.c \
		state.c \
		time.c

OBJ		= $(SRC:.c=.o)

NAME	= philo
CC		= cc -Wall -Werror -Wextra #-fsanitize=thread
RM		= rm -f

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $^ -o $@

%.o:%.c philo.h
	$(CC) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean