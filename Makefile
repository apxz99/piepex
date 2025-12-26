# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/19 08:50:18 by sarayapa          #+#    #+#              #
#    Updated: 2025/12/26 09:37:17 by sarayapa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
FILES = pipex.c ft_strlen.c ft_split.c ft_strjoin.c \
		ft_strncmp.c ft_calloc.c ft_bzero.c ft_memset.c \
		pipex_utils.c ft_putstr_fd.c ft_strrchr.c

SRCS = srcs/
BUILD = build/
INC = -I .
SRCS_O = $(addprefix $(BUILD), $(FILES:.c=.o))
CFLAGS = -Wall -Wextra -Werror

all: $(BUILD) $(NAME)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)%.o: $(SRCS)%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(SRCS_O)
	$(CC) $(CFLAGS) $^ $(INC) -o $@

debug: all $(NAME)

clean:
	rm -rf $(BUILD) valgrind.rpt a.out input output

fclean: clean
	rm -f $(NAME) pipex

re:fclean all

.PHONY: all clean fclean re debug