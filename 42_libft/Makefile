# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 09:51:03 by lwidmer           #+#    #+#              #
#    Updated: 2022/12/16 10:44:22 by lwidmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FILENAMES = ft_isalpha \
			ft_isdigit \
			ft_isprint \
			ft_isascii \
			ft_isalnum \
			ft_strlen \
			ft_memset \
			ft_bzero \
			ft_memcpy \
			ft_memmove \
			ft_memchr \
			ft_memcmp \
			ft_putchar_fd \
			ft_putstr_fd \
			ft_putendl_fd \
			ft_putnbr_fd \
			ft_itoa \
			ft_strdup \
			ft_strmapi \
			ft_striteri \
			ft_strlcpy \
			ft_strlcat \
			ft_toupper \
			ft_tolower \
			ft_strchr \
			ft_strrchr \
			ft_strncmp \
			ft_strnstr \
			ft_atoi \
			ft_substr \
			ft_strjoin \
			ft_strtrim \
			ft_split \
			ft_calloc

BONUS_FILENAMES = ft_lstnew_bonus \
			ft_lstadd_front_bonus \
			ft_lstsize_bonus \
			ft_lstlast_bonus \
			ft_lstadd_back_bonus \
			ft_lstdelone_bonus \
			ft_lstclear_bonus \
			ft_lstiter_bonus \
			ft_lstmap_bonus

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILENAMES)))
SRCS_B = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(BONUS_FILENAMES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILENAMES)))
OBJS_B = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(BONUS_FILENAMES)))
CFLAGS = -Werror -Wall -Wextra

${NAME}: ${OBJS}
	ar rc $@ $^
	ranlib ${NAME}

.c.o: ${SRCS}
	cc ${CFLAGS} -c -o $@ $<

all: ${NAME}

clean:
	rm -rf ${OBJS} ${OBJS_B}

fclean: clean
	rm -rf ${NAME}

re: fclean all

bonus: ${OBJS} ${OBJS_B}
	ar rc ${NAME} ${OBJS} ${OBJS_B}
	ranlib ${NAME}

.PHONY: all clean fclean re bonus
