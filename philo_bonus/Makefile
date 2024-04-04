# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 01:46:42 by emagueri          #+#    #+#              #
#    Updated: 2024/04/03 22:26:42 by emagueri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	ft_atoi.c \
		init.c \
		philo.c \
		state.c \
		time.c \
		ft_strlen.c \
		ft_strlcpy.c \
		main.c

OBJ		= $(SRC:.c=.o)

NAME	= philo_bonus
CC		= cc -Wall -Werror -Wextra 
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