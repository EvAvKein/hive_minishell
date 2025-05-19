# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 08:44:47 by ekeinan           #+#    #+#              #
#    Updated: 2025/05/19 13:47:30 by ahavu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

SRC_DIR := sources

SRC_FILES := main.c \
			 signal_handlers.c \
			 utils/cleanup.c \
			 utils/printing.c \
			 utils/tiny_checks.c \
			 execution/builtin_or_sys_command.c \
			 execution/commands.c \
			 execution/commands_ms_cd.c \
			 execution/commands_ms_export.c \
			 execution/commands_ms_unset.c \
			 execution/execution.c \
			 execution/pipeline.c \
			 execution/pipeline_utils.c \
			 execution/redirections.c \
			 execution/utils.c \
			 parsing/parsing.c \
			 parsing/expansion/env.c \
			 parsing/expansion/expand.c \
			 parsing/expansion/delete_void_expansions.c \
			 parsing/operators/heredoc.c \
			 parsing/operators/redirections.c \
			 parsing/operators/control_flow.c \
			 parsing/node_sorting_utils.c \
			 parsing/node_handling.c \
			 parsing/arg_handling.c \
			 parsing/num_utils.c \
			 parsing/misc.c

INCLUDE_DIR := includes
INCLUDE_FILES := minishell.h parsing.h

LIBFT_DIR := libft_plus
LIBFT_LIB := $(LIBFT_DIR)/libft_plus.a

COMPILE_FLAGS := -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(LIBFT_DIR)/include
LIBRARY_FLAGS := -lreadline
DEBUG_FLAGS := -g

SRC_OBJ := $(SRC_FILES:%.c=$(SRC_DIR)/%.o)
HEADERS := $(INCLUDE_FILES:%=$(INCLUDE_DIR)/%)
LIBFT_HEADERS := $(LIBFT_DIR)/libft_plus.h $(LIBFT_INCLUDE_FILES:%=$(LIBFT_INCLUDE_DIR)/%)

all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR) -s --no-print-directory

%.o: %.c
	cc $(COMPILE_FLAGS) -c $< -o $@

$(NAME): $(LIBFT_LIB) $(SRC_OBJ) $(HEADERS) $(LIBFT_HEADERS)
	cc $(COMPILE_FLAGS) $(SRC_OBJ) $(LIBFT_LIB) -o $(NAME) $(LIBRARY_FLAGS)

clean:
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	@rm -f $(SRC_OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	@rm -f $(NAME)

re: fclean all

neat: $(NAME) clean
	clear

verbose: export VERBOSE = 1
verbose: re

debug: COMPILE_FLAGS += $(DEBUG_FLAGS)
debug: re

.PHONY: all clean fclean re neat debug
