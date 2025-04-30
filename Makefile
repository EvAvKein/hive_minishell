# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 08:44:47 by ekeinan           #+#    #+#              #
#    Updated: 2025/04/30 08:37:47 by ahavu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

SRC_DIR := sources
MAIN := main.c
SRC_FILES := utils/spaces.c \
			 utils/cleanup.c \
			 utils/printing.c \
			 execution/builtin_or_sys_command.c \
			 execution/commands.c \
			 execution/commands_ms_cd.c \
			 execution/commands_ms_export.c \
			 execution/commands_ms_unset.c \
			 execution/execution.c \
			 execution/pipe.c \
			 execution/pipeline.c \
			 execution/redirections.c \
			 execution/utils.c \
			 parsing/parsing.c \
			 parsing/traversal.c \
			 parsing/misc.c \
			 parsing/arg_handling.c \
			 parsing/node_handling.c \
			 parsing/node_sorting_utils.c \
			 parsing/operator_handling.c \
			 parsing/operators/assignments.c \
			 parsing/operators/redirections.c \

INCLUDE_DIR := includes
INCLUDE_FILES := minishell.h parsing.h

LIBFT_DIR := libft_plus
LIBFT_LIB := $(LIBFT_DIR)/libft_plus.a

COMPILE_FLAGS := -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(LIBFT_DIR)/include
LIBRARY_FLAGS := -lreadline
DEBUG_FLAGS := -g

MAIN_OBJ := $(MAIN:%.c=$(SRC_DIR)/%.o)
SRC_OBJ := $(SRC_FILES:%.c=$(SRC_DIR)/%.o)
HEADERS := $(INCLUDE_FILES:%=$(INCLUDE_DIR)/%)
LIBFT_HEADERS := $(LIBFT_DIR)/libft_plus.h $(LIBFT_INCLUDE_FILES:%=$(LIBFT_INCLUDE_DIR)/%)

all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR) -s --no-print-directory

%.o: %.c
	cc $(COMPILE_FLAGS) -c $< -o $@

$(NAME): $(LIBFT_LIB) $(SRC_OBJ) $(MAIN_OBJ) $(HEADERS) $(LIBFT_HEADERS)
	cc $(COMPILE_FLAGS) $(SRC_OBJ) $(MAIN_OBJ) $(LIBFT_LIB) -o $(NAME) $(LIBRARY_FLAGS)

clean:
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	@rm -f $(MAIN_OBJ) $(SRC_OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	@rm -f $(NAME)

re: fclean all

neat: $(NAME) clean
	clear

debug: COMPILE_FLAGS += $(DEBUG_FLAGS)
debug: re

.PHONY: all clean fclean re neat debug
