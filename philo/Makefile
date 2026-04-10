# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jemustaj <jemustaj@student.42Porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/09 15:47:53 by jemustaj          #+#    #+#              #
#    Updated: 2026/04/09 15:59:01 by jemustaj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-g -fsanitize=address

SRC = main.c \
	  parse_input.c \
	  init_variables.c \
	  run_simulation.c \
	  routine_simulation.c \
	  monitor_simulation.c \
	  end_simulation.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rdf $(OBJ)

fclean: clean
	rm -rdf $(NAME)

re: fclean all
