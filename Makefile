# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 08:44:47 by ekeinan           #+#    #+#              #
#    Updated: 2025/04/09 16:52:33 by ekeinan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

SRC_DIR := sources
SRC_FILES := main.c \
			 utils/cleanup.c \
			 parsing/parsing.c \
			 parsing/input_to_nodes.c

INCLUDE_DIR := includes
INCLUDE_FILES := minishell.h

LIBFT_DIR := libft_plus
LIBFT_LIB := $(LIBFT_DIR)/libft_plus.a

COMPILE_FLAGS := -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(LIBFT_DIR)/include
LIBRARY_FLAGS := -lreadline
DEBUG_FLAGS := -g

OBJ := $(SRC_FILES:%.c=$(SRC_DIR)/%.o)
HEADERS := $(INCLUDE_FILES:%=$(INCLUDE_DIR)/%)
LIBFT_HEADERS := $(LIBFT_DIR)/libft_plus.h $(LIBFT_INCLUDE_FILES:%=$(LIBFT_INCLUDE_DIR)/%)

all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR) -s --no-print-directory

%.o: %.c
	cc $(COMPILE_FLAGS) -c $< -o $@

$(NAME): $(LIBFT_LIB) $(OBJ) $(HEADERS) $(LIBFT_HEADERS)
	cc $(COMPILE_FLAGS) $(LIBRARY_FLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	@rm -f $(OBJ) $(OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	@rm -f $(NAME)

re: fclean all

neat: $(NAME) clean
	clear

debug: COMPILE_FLAGS += $(DEBUG_FLAGS)
debug: re

.PHONY: all clean fclean re neat debug
