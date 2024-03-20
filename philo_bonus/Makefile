# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 01:46:42 by emagueri          #+#    #+#              #
#    Updated: 2024/03/20 15:41:51 by emagueri         ###   ########.fr        #
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
CC		= cc -Wall -Werror -Wextra  #-fsanitize=thread -pthread
RM		= rm -f

bonus:$(NAME)

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