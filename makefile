# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/06 12:27:16 by alejogogi         #+#    #+#              #
#    Updated: 2025/07/10 18:31:41 by alejogogi        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra
SCR_DIR = ./src
SRC = ./src/main.c ./src/free_mem.c ./src/init_mutex.c ./src/routine.c ./src/function_aux.c ./src/init_philo.c
OBJ = $(SRC:.c=.o)

INCLUDE =include/philo.h

RM = rm -f

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

	@clear
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(OBJ) $(NAME)

re: fclean all