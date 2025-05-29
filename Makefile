# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 08:44:47 by ekeinan           #+#    #+#              #
#    Updated: 2025/05/30 12:39:18 by ahavu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

VERBOSE ?= 0
MINI_LS ?= 0
SETTINGS = -DVERBOSE=$(VERBOSE) -DMINI_LS=$(MINI_LS)

SRC_DIR := sources
SRC_FILES := main.c \
			 prompt.c \
			 signal_handlers.c \
			 env/env.c \
			 env/checks.c \
			 env/getters.c \
			 env/setters.c \
			 utils/str_arr.c \
			 utils/cleanup.c \
			 utils/printing.c \
			 utils/tiny_checks.c \
			 execution/builtin_or_ext_command.c \
			 execution/builtins_1.c \
			 execution/builtins_2.c \
			 execution/builtins_ms_cd.c \
			 execution/builtins_ms_export.c \
			 execution/builtins_ms_export_utils.c \
			 execution/execution.c \
			 execution/helpers.c \
			 execution/pipeline.c \
			 execution/pipeline_utils.c \
			 execution/pipeline_parent_and_child.c \
			 execution/redirections.c \
			 execution/utils.c \
			 execution/utils_atoll.c \
			 parsing/misc.c \
			 parsing/parsing.c \
			 parsing/num_utils.c \
			 parsing/arg_handling.c \
			 parsing/node_handling.c \
			 parsing/node_sorting_utils.c \
			 parsing/operators/heredoc.c \
			 parsing/operators/redirections.c \
			 parsing/operators/control_flow.c \
			 parsing/expansion/expand.c \
			 parsing/expansion/delete_void_expansions.c

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
	cc $(COMPILE_FLAGS) $(SETTINGS) -c $< -o $@

$(NAME): $(LIBFT_LIB) $(SRC_OBJ) $(HEADERS) $(LIBFT_HEADERS)
	cc $(COMPILE_FLAGS) $(SRC_OBJ) $(LIBFT_LIB) $(SETTINGS) -o $(NAME) $(LIBRARY_FLAGS)

clean:
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	@rm -f $(SRC_OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) $@ --no-print-directory
	@rm -f $(NAME)

re: fclean all

neat: $(NAME) clean
	clear

more: export VERBOSE = 1
more: export MINI_LS = 1
more: re

debug: COMPILE_FLAGS += $(DEBUG_FLAGS)
debug: re

.PHONY: all clean fclean re neat verbose debug
