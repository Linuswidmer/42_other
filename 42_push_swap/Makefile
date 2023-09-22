# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/26 19:41:22 by lwidmer           #+#    #+#              #
#    Updated: 2023/04/09 16:11:21 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

FILENAMES_FT_PRINTF = ft_strlen ft_putchar_fd ft_putstr_fd ft_intlen_base ft_printf ft_strlcpy ft_print_address_hex ft_putnbr_base ft_strdup

FILENAMES_PUSH_SWAP = main ft_split check_input stack swap rotate \
	push print utils terminate init sort sort_two_three sort_four_five \
	sort chunk_sort chunk_sort_utils parse apply_rotations

SRCS_FT_PRINTF = ./srcs_ft_printf/
SRCS_PUSH_SWAP = ./srcs_push_swap/
SRCS = $(addprefix $(SRCS_FT_PRINTF), $(addsuffix .c, $(FILENAMES_FT_PRINTF)) $(addprefix $(SRCS_PUSH_SWAP), $(addsuffix .c, $(FILENAMES_PUSH_SWAP))))

OBJS_FT_PRINTF = ./srcs_ft_printf/
OBJS_PUSH_SWAP = ./srcs_push_swap/
OBJS = $(addprefix $(OBJS_FT_PRINTF), $(addsuffix .o, $(FILENAMES_FT_PRINTF))) $(addprefix $(OBJS_PUSH_SWAP), $(addsuffix .o, $(FILENAMES_PUSH_SWAP)))

CFLAGS = -Werror -Wall -Wextra

INCLUDES_DIR = -I ./includes

${NAME}: ${OBJS}
	cc -o push_swap $^

.c.o: ${SRCS}
	cc ${CFLAGS} -c -o $@ $< ${INCLUDES_DIR}

all: ${NAME}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re

build_visualizer:
	git clone git@github.com:o-reo/push_swap_visualizer.git
	cd push_swap_visualizer && mkdir build
	cd push_swap_visualizer/build && cmake .. && make

build_tester:
	wget https://projects.intra.42.fr/uploads/document/document/13507/checker_linux
	chmod 777 checker_linux
	git clone git@github.com:Linuswidmer/push_swap_tester.git	

test_three:
	make -C ./push_swap_tester test_three

test_four:
	make -C ./push_swap_tester test_four

test_five:
	make -C ./push_swap_tester test_five

test_random: 
	make -C ./push_swap_tester test_random

test_stats: 
	make -C ./push_swap_tester test_stats
