# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/29 17:32:46 by sarayapa          #+#    #+#              #
#    Updated: 2025/12/04 18:38:39 by sarayapa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FILES = ft_atoi.c  ft_isalnum.c  ft_isalpha.c \
		ft_isascii.c  ft_isdigit.c  ft_isprint.c \
		ft_memset.c  ft_strlen.c  ft_strncmp.c  \
		ft_tolower.c  ft_toupper.c ft_bzero.c \
		ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		ft_strchr.c	ft_strrchr.c ft_memchr.c \
		ft_strnstr.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c \
		ft_split.c ft_memcmp.c ft_memcpy.c \
		ft_itoa.c ft_strmapi.c \
		ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putnbr_fd.c ft_putendl_fd.c \
		ft_calloc.c ft_isalnum.c

BONUS = ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstiter_bonus.c \
		ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c \
		ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstmap_bonus.c

SRCS = sources
BUILD = build
INC = -I .
CC = cc
SRCS_O = $(addprefix $(BUILD)/, $(FILES:.c=.o))
BONUS_O = $(addprefix $(BUILD)/, $(BONUS:.c=.o))
ARCHIVE = ar rcs
CFLAGS = -Wall -Wextra -Werror

all: $(BUILD) $(NAME)

$(BUILD):
	mkdir -p $(BUILD)/

$(BUILD)/%.o: $(SRCS)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(SRCS_O) $(BONUS_O)
	$(ARCHIVE) $@ $^

debug: all $(NAME)
	clear && $(CC) $(CFLAGS) -g pipex.c libft.a -lbsd -o pipex
#clear && $(CC) $(CFLAGS) *.c libft.a -lbsd && valgrind --leak-check=full -s --log-file=valgrind.rpt ./a.out

bonus: $(BUILD) $(SRCS_O) $(BONUS_O)
	$(ARCHIVE) $(NAME) $(BONUS_O)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME) valgrind.rpt a.out input output pipex

re:fclean all

.PHONY: all clean fclean re debug