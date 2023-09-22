# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 17:10:01 by lwidmer           #+#    #+#              #
#    Updated: 2023/03/24 11:00:28 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

FILENAMES_PIPEX = pipe pipe_utils init parse parse_utils terminate terminate_utils

SRCS_PIPEX = ./srcs_pipex/
SRCS = $(addprefix $(SRCS_PIPEX), $(addsuffix .c, $(FILENAMES_PIPEX)))

OBJS_PIPEX = ./srcs_pipex/
OBJS = $(addprefix $(OBJS_PIPEX), $(addsuffix .o, $(FILENAMES_PIPEX)))

CFLAGS = -Werror -Wall -Wextra

INCLUDES_DIR = -I ./includes

${NAME}: ${OBJS}
	cc -o ${NAME} $^ -L. ./libft/libft.a

.c.o: ${SRCS}
	cc ${CFLAGS} -c -o $@ $< ${INCLUDES_DIR}

lib:
	make -C ./libft

all: lib ${NAME}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re

