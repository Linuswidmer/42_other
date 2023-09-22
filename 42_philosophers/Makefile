# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 13:46:23 by lwidmer           #+#    #+#              #
#    Updated: 2023/07/16 13:01:04 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FILENAMES = philo philo_routine philo_monitor philo_utils \
			philo_init philo_print philo_free libft_utils

SRCS_DIR = ./srcs/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILENAMES)))

OBJS_DIR = ./srcs/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILENAMES)))

CFLAGS = -Werror -Wall -Wextra

INCLUDES_DIR = -I ./includes/

all: ${NAME}

${NAME}: ${OBJS}
	cc -o ${NAME} $^ 

%.o: %.c
	cc -c -o $@ $< ${INCLUDES_DIR} ${CFLAGS}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

val: re
	valgrind ./philo 4 1200 200 200 5

hel: re
	valgrind --tool=helgrind ./philo 5 1200 200 200 5
